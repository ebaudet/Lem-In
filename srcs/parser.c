/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 20:17:54 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/19 20:17:54 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"

int		pars_in(void)
{
	char	*line;
	char	**tmp;
	int		ret;

	if (get_next_line(FD, &line) > 0)
		add_nb_ant(line);
	while (get_next_line(FD, &line) > 0)
	{
		if (!ft_strcmp(line, "##start"))
			ret = add_position(FD, START);
		else if (!ft_strcmp(line, "##end"))
			ret = add_position(FD, END);
		else if (line[0] == '#')
			continue ;
		else if (tmp = ft_strsplit(line, ' ') && tmp[1])
			ret = add_room(tmp);
		else if (free_tab(tmp) && tmp = ft_strsplit(line, '-') && tmp[1])
			ret = add_pipe(tmp);
		else if (free_tab(tmp))
			return (-1);
		free(tmp);
		if (ret == -1)
			return (-1);
	}
	return (0);
}

int		add_position(int fd, int pos)
{
	char	*line;
	char	**tmp;
	int		ret;

	if ((get_next_line(FD, &line) > 0) && tmp = ft_strsplit(line, ' ')
		&& tmp[1])
	{
		ret = add_room(tmp);
		if (ret != -1)

	}
}

int		add_room(char **room, int pos)
{
	int		i;
	int		x;
	int		y;
	t_data	*d;

	i = 0;
	while (room[i])
		i++;
	if (i != 3)
		return (-1);
	if (!ft_is_number(room[1]) || !ft_is_number(room[2]))
		return (-1);
	x = ft_atoi(room[1]);
	y = ft_atoi(room[2])
	free(room[1]);
	free(room[2]);
	list_add_room(room[0], x, y);
	if (pos == START)

	return (0);
}

int		add_pipe(char **pipe)
{
	int		i;

	i = 0;
	while (pipe[i])
		i++;
	if (i != 2)
		return (-1);
	return (list_add_pipe(pipe[0], pipe[i]));
}
