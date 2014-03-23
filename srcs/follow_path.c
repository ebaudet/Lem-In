/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 22:42:05 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/23 22:48:51 by ebaudet          ###   ########.fr       */
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
	d->path = d->path->next;
	tmp = d->path;
	tmp->this_ant = new_lemin;
	tmp->ant += 1;
	if (d->path->room != d->end)
		print_lemin(tmp->this_ant, tmp->room->name, -1);
	new_lemin++;
	while (d->ant && d->ant_end != d->ant)
	{
		i = 0;
		tmp = d->path;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp->prev)
		{
			in_node(tmp, &new_lemin, &i, d);
			tmp = tmp->prev;
		}
		ft_putchar('\n');
	}
}

void	in_node(t_path *tmp, int *new_lemin, int *i, t_data *d)
{
	if (d->path->room == d->end)
	{
		all_at_the_end(d);
		return ;
	}
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

void	all_at_the_end(t_data *d)
{
	int		i;

	i = 0;
	while (i < d->ant)
	{
		print_lemin(i + 1, d->end->name, i);
		i++;
	}
	d->ant_end = d->ant_start;
	d->ant_start = 0;
}
