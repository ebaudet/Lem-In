/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 20:31:32 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/23 20:31:32 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"

t_path	*new_path(t_path *prev, t_room *room, t_path *next, int ant)
{
	t_path	*new;

	if ((new = (t_path *)malloc(sizeof(t_path))) == 0)
		ft_error("error malloc new path");
	new->room = room;
	new->prev = prev;
	new->next = next;
	new->ant = ant;
	new->this_ant = 0;
	return (new);
}

void	add_end_path(t_data *d, t_room *room)
{
	t_path	*tmp;

	if (!d->path)
		d->path = new_path(NULL, room, NULL, d->ant);
	else
	{
		tmp = d->path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_path(tmp, room, NULL, 0);
	}
}

int		delete_last_path(t_data *d)
{
	t_path	*tmp;

	if (!d->path)
		return (0);
	tmp = d->path;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp == d->path)
	{
		free(d->path);
		d->path = NULL;
	}
	else
	{
		tmp->prev->next = NULL;
		free(tmp);
		tmp = NULL;
	}
	return (1);
}
