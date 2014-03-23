/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 22:42:05 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/23 02:25:20 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"

void	follow_path(t_data *d)
{
	t_path		*tmp;
	int			new_lemin;
	int			i;

	new_lemin = 1;
	tmp = d->path;
	tmp->this_ant = new_lemin;
	tmp->ant += 1;
	print_lemin(tmp->this_ant, tmp->room->name, -1);
	new_lemin++;
	while (d->ant && d->ant_end != d->ant)
	{
		i = 0;
		tmp = d->path;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp)
		{
			in_node(tmp, &new_lemin, &i, d);
			tmp = tmp->prev;
		}
		ft_putchar('\n');
	}
}

void	in_node(t_path *tmp, int *new_lemin, int *i, t_data *d)
{
	if (tmp->ant != 0 && tmp->room != d->end)
	{
		tmp->next->this_ant = tmp->this_ant;
		tmp->next->ant += tmp->ant;
		print_lemin(tmp->this_ant, tmp->next->room->name, (*i)++);
		tmp->this_ant = 0;
		tmp->ant -= tmp->ant;
		if (tmp->next->room == d->end)
			d->ant_end++;
	}
	if (tmp == d->path && *new_lemin <= d->ant_start)
	{

		tmp->this_ant = *new_lemin;
		tmp->ant += 1;
		print_lemin(tmp->this_ant, tmp->room->name, (*i)++);
		(*new_lemin)++;
	}
}
