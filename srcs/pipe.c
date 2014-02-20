/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 23:22:04 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/19 23:22:04 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"

t_pipe	*pipe_new(t_room *room)
{
	t_pipe	*pipe;

	if ((pipe = (t_pipe *)malloc(sizeof(t_pipe))) == NULL)
		ft_error("error malloc new pipe");
	pipe->next = NULL;
	pipe->room = room;
	return (pipe);
}

int		list_add_pipe(char *room1, char *room2)
{
	t_data	*d;
	t_room	*tmp;
	t_room	*ptr_room1;
	t_room	*ptr_room2;

	ptr_room1 = NULL;
	ptr_room2 = NULL;
	d = data_init();
	tmp = *(d->list_room);
	while (tmp && !(ptr_room1 && ptr_room2))
	{
		if (!ft_strcmp(tmp->name, room2))
			ptr_room2 = tmp;
		if (!ft_strcmp(tmp->name, room1))
			ptr_room1 = tmp;
		tmp = tmp->next;
	}
	if (!ptr_room1 || !ptr_room2)
		return (-1);
	pipe_room(ptr_room1, ptr_room2);
	pipe_room(ptr_room2, ptr_room1);
	return (0);
}

void	pipe_room(t_room *room, t_room *pipe)
{
	t_pipe	*tmp;

	if (!room->pipe)
		room->pipe = pipe_new(pipe);
	else
	{
		tmp = room->pipe;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = pipe_new(pipe);
	}
}
