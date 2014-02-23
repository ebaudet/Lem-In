/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 23:17:03 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/19 23:17:03 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"

t_room	*new_room(char *name, int x, int y)
{
	t_room	*room;

	if ((room = (t_room *)malloc(sizeof(t_room))) == NULL)
		return (NULL);
	room->x = x;
	room->y = y;
	room->name = name;
	room->next = NULL;
	room->pipe = NULL;
	room->path = 0;
	return (room);
}

t_room	*list_add_room(char *name, int x, int y)
{
	t_data	*d;
	t_room	*tmp;
	t_room	*room;

	d = data_init();
	tmp = *(d->list_room);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name) || (tmp->x == x && tmp->y == y))
			return (NULL);
		tmp = tmp->next;
	}
	if ((room = new_room(name, x, y)) == NULL)
		return (NULL);
	tmp = *(d->list_room);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		*(d->list_room) = room;
	else
		tmp->next = room;
	return (room);
}

void	count_room(void)
{
	t_data	*d;
	int		len;
	t_room	*tmp;

	d = data_init();
	tmp = *(d->list_room);
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	d->nb_room = len;
}
