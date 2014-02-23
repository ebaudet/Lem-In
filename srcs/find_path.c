/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 22:23:49 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/23 22:23:49 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		search_end(t_room *pos, t_data *d)
{
	t_pipe		*tmp;

	tmp = pos->pipe;
	while (tmp)
	{
		if (tmp->room == d->end)
		{
			tmp->room->path = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	find_path(t_data *d)
{
	t_room		*scout;

	scout = d->start;
	add_end_path(d, scout);
	while (scout && scout != d->end)
	{
		scout->path = 1;
		if (!find_good_node(&scout, 0, d))
		{
			if (!find_good_node(&scout, 1, d))
				ft_error("ERROR");
		}
	}
}

int		find_good_node(t_room **scout, int find, t_data *d)
{
	t_pipe		*tmp;

	tmp = (*scout)->pipe;
	while (tmp)
	{
		if (tmp->room->path == find)
		{
			if (find == 0)
			{
				tmp->room->path = 1;
				*scout = tmp->room;
				add_end_path(d, *scout);
			}
			else
			{
				(*scout)->path = -1;
				delete_last_path(d);
				*scout = tmp->room;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
