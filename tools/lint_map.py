#!/usr/bin/env python3
"""Lint Lem-In map files and report line-numbered diagnostics."""

import argparse
import re
import sys
from collections import defaultdict, deque
from dataclasses import dataclass


INT_RE = re.compile(r"^[+-]?[0-9]+$")


@dataclass
class Issue:
    line: int
    level: str
    message: str


class MapLinter:
    def __init__(self, filename, show_warnings=False):
        self.filename = filename
        self.show_warnings = show_warnings
        self.issues = []
        self.rooms = {}
        self.coords = {}
        self.tunnels = set()
        self.graph = defaultdict(set)
        self.start = None
        self.end = None
        self.ant_count = None
        self.pending_command = None
        self.seen_tunnel = False

    def error(self, line, message):
        self.issues.append(Issue(line, "error", message))

    def warning(self, line, message):
        if self.show_warnings:
            self.issues.append(Issue(line, "warning", message))

    def lint(self):
        try:
            with open(self.filename, "r", encoding="utf-8") as f:
                lines = f.readlines()
        except OSError as exc:
            self.error(0, str(exc))
            return self.issues

        for line_no, raw in enumerate(lines, 1):
            line = raw.rstrip("\n")
            if line.endswith("\r"):
                line = line[:-1]
            self.parse_line(line_no, line)

        self.finish(len(lines))
        return self.issues

    def parse_line(self, line_no, line):
        if line == "":
            self.error(line_no, "empty lines are not valid map entries")
            return
        if line.startswith("#"):
            self.parse_comment_or_command(line_no, line)
            return
        if self.ant_count is None:
            self.parse_ant_count(line_no, line)
            return
        if " " in line:
            self.parse_room(line_no, line)
            return
        if "-" in line:
            self.parse_tunnel(line_no, line)
            return
        self.error(line_no, "expected a room line or tunnel line")

    def parse_comment_or_command(self, line_no, line):
        if line not in ("##start", "##end"):
            if line.startswith("##"):
                self.warning(line_no, "unknown command is treated as a comment")
            return
        if self.ant_count is None:
            self.error(line_no, "%s appears before the ant count" % line)
            return
        if self.pending_command is not None:
            self.error(
                line_no,
                "%s appears before a room was assigned to %s"
                % (line, self.pending_command),
            )
        self.pending_command = line

    def parse_ant_count(self, line_no, line):
        if not INT_RE.match(line):
            self.error(line_no, "first non-comment line must be an integer ant count")
            return
        self.ant_count = int(line)
        if self.ant_count <= 0:
            self.error(line_no, "ant count must be greater than zero")

    def parse_room(self, line_no, line):
        fields = line.split()
        if len(fields) != 3:
            self.error(line_no, "room lines must contain: name x y")
            self.pending_command = None
            return
        name, x_str, y_str = fields
        if self.seen_tunnel:
            self.error(line_no, "room declared after tunnel section started")
        if name.startswith("L"):
            self.error(line_no, "room name must not start with 'L'")
        if name.startswith("#"):
            self.error(line_no, "room name must not start with '#'")
        if "-" in name:
            self.error(line_no, "room name must not contain '-'")
        if not INT_RE.match(x_str) or not INT_RE.match(y_str):
            self.error(line_no, "room coordinates must be integers")
            self.pending_command = None
            return
        coord = (int(x_str), int(y_str))
        if name in self.rooms:
            self.error(
                line_no,
                "duplicate room name '%s' first declared on line %d"
                % (name, self.rooms[name]),
            )
        else:
            self.rooms[name] = line_no
        if coord in self.coords:
            self.error(
                line_no,
                "duplicate coordinates %s %s first used on line %d"
                % (x_str, y_str, self.coords[coord]),
            )
        else:
            self.coords[coord] = line_no
        if self.pending_command == "##start":
            if self.start is not None:
                self.error(line_no, "start room already set on line %d" % self.start[1])
            self.start = (name, line_no)
        elif self.pending_command == "##end":
            if self.end is not None:
                self.error(line_no, "end room already set on line %d" % self.end[1])
            self.end = (name, line_no)
        self.pending_command = None

    def parse_tunnel(self, line_no, line):
        parts = line.split("-")
        if len(parts) != 2 or not parts[0] or not parts[1]:
            self.error(line_no, "tunnel lines must contain exactly: room1-room2")
            self.pending_command = None
            return
        if self.pending_command is not None:
            self.error(line_no, "%s must be followed by a room, not a tunnel" %
                       self.pending_command)
            self.pending_command = None
        left, right = parts
        self.seen_tunnel = True
        if left not in self.rooms:
            self.error(line_no, "unknown room '%s' in tunnel" % left)
        if right not in self.rooms:
            self.error(line_no, "unknown room '%s' in tunnel" % right)
        if left == right:
            self.warning(line_no, "self-loop tunnel '%s-%s'" % (left, right))
        key = tuple(sorted((left, right)))
        if key in self.tunnels:
            self.warning(line_no, "duplicate tunnel '%s-%s'" % (left, right))
        else:
            self.tunnels.add(key)
        if left in self.rooms and right in self.rooms:
            self.graph[left].add(right)
            self.graph[right].add(left)

    def finish(self, last_line):
        if self.ant_count is None:
            self.error(last_line, "missing ant count")
        if self.pending_command is not None:
            self.error(last_line, "%s is not followed by a room" % self.pending_command)
        if self.start is None:
            self.error(last_line, "missing ##start room")
        if self.end is None:
            self.error(last_line, "missing ##end room")
        if not self.tunnels:
            self.error(last_line, "missing tunnel section")
        if self.start and self.end and not self.has_path(self.start[0], self.end[0]):
            self.error(last_line, "no tunnel path connects ##start to ##end")

    def has_path(self, start, end):
        queue = deque([start])
        visited = {start}
        while queue:
            room = queue.popleft()
            if room == end:
                return True
            for next_room in self.graph[room]:
                if next_room not in visited:
                    visited.add(next_room)
                    queue.append(next_room)
        return False


def print_issues(filename, issues):
    if not issues:
        print("%s: OK" % filename)
        return
    for issue in issues:
        location = filename
        if issue.line > 0:
            location += ":%d" % issue.line
        print("%s: %s: %s" % (location, issue.level, issue.message))


def main(argv):
    parser = argparse.ArgumentParser(description="Lint Lem-In map files.")
    parser.add_argument(
        "--warnings",
        action="store_true",
        help="also report non-fatal issues such as duplicate tunnels",
    )
    parser.add_argument("maps", nargs="+", help="map file(s) to lint")
    args = parser.parse_args(argv)

    has_error = False
    for filename in args.maps:
        issues = MapLinter(filename, args.warnings).lint()
        print_issues(filename, issues)
        if any(issue.level == "error" for issue in issues):
            has_error = True
    return 1 if has_error else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
