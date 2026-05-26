# Lem-In

Lem-In is a 42 school algorithm project written in C. The program reads an ant
farm description from standard input, finds a path from the start room to the
end room, then prints the sequence of moves needed to send the ants through the
farm.

The executable is named `lem-in`.

## Project Goal

Given:

- a number of ants,
- a list of rooms with coordinates,
- one start room,
- one end room,
- and a list of tunnels between rooms,

the program must move every ant from `##start` to `##end`. Output moves use the
format:

```text
L<ant_number>-<room_name>
```

For example, `L3-room_b` means ant 3 moved to room `room_b`.

## Build

Compile the project with:

```sh
make
```

This builds:

- `libft/libft.a`
- `lem-in`

Useful Makefile targets:

```sh
make        # build the executable
make clean  # remove object files
make fclean # remove object files and lem-in
make re     # rebuild from scratch
make gdb    # build with debug symbols and start gdb
```

## Run

`lem-in` reads from standard input:

```sh
./lem-in < sujet1.map
```

You can also pipe a generated or handwritten map:

```sh
cat test.map | ./lem-in
```

If the input is invalid or no path can be found, the program prints:

```text
ERROR
```

## Input Format

A valid map has this structure:

```text
<number_of_ants>
##start
<start_room_name> <x> <y>
##end
<end_room_name> <x> <y>
<room_name> <x> <y>
<room_name>-<room_name>
```

Rules handled by this implementation:

- The first non-comment line must be a positive integer ant count.
- Comments begin with `#`.
- `##start` marks the next room as the start room.
- `##end` marks the next room as the end room.
- Room lines contain exactly three fields: name, x coordinate, y coordinate.
- Tunnel lines contain exactly two room names separated by `-`.
- Room names must be unique.
- Room coordinates must be unique.
- A tunnel can only reference rooms that were already declared.

## Example Map

```text
3
##start
0 1 0
##end
1 5 0
2 9 0
3 13 0
0-2
2-3
3-1
```

Run it with:

```sh
./lem-in < sujet1.map
```

On a successful run, the program first echoes the parsed colony, then prints a
blank line, then prints one line per turn containing the ants moved during that
turn.

Move output looks like:

```text
L1-2
L1-3 L2-2
L1-1 L2-3 L3-2
L2-1 L3-3
L3-1
```

## Included Maps

The repository includes several map files that can be used for manual testing:

- `sujet1.map`
- `test.map`
- `advanced.map`
- `lol.map`
- `stupid.map`, an invalid map useful for checking error handling

Run any of them with:

```sh
./lem-in < <map_file>
```

## Project Layout

```text
.
|-- Makefile
|-- includes/
|   `-- lem-in.h
|-- libft/
|   |-- Makefile
|   `-- ...
|-- srcs/
|   |-- main.c
|   |-- parser.c
|   |-- data.c
|   |-- room.c
|   |-- pipe.c
|   |-- path.c
|   |-- find_path.c
|   |-- follow_path.c
|   |-- print.c
|   |-- error.c
|   |-- tools.c
|   `-- ft_is_number.c
`-- *.map
```

Main modules:

- `srcs/main.c`: initializes data, parses input, finds a path, and prints moves.
- `srcs/parser.c`: reads and validates the map from standard input.
- `srcs/room.c`: creates rooms and stores them in the room list.
- `srcs/pipe.c`: creates bidirectional tunnels between rooms.
- `srcs/path.c`: manages the selected path.
- `srcs/find_path.c`: searches for a path from start to end.
- `srcs/follow_path.c`: moves ants along the selected path.
- `srcs/print.c`: prints the colony and ant moves.
- `libft/`: custom C utility library used by the project.

## Notes

- This implementation searches and follows one path through the colony.
- The program does not take command-line arguments.
- Input is consumed from file descriptor `0`, standard input.
- The project is built with `gcc` and the flags `-Wall -Wextra -Werror`.
