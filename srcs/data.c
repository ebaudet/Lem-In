/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 20:14:01 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/19 20:14:01 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"
#include "libft.h"

t_data	*data_init(void)
{
	static t_data	*d = NULL;

	if (!d)
	{
		if ((d = (t_data *)malloc(sizeof(t_data))) == 0)
			ft_error("error malloc data");
		d->start = NULL;
		d->end = NULL;
		if ((d->list_room = (t_room **)malloc(sizeof(t_room))) == NULL)
			ft_error("error malloc pointer room");
		d->path = NULL;
	}
	return (d);
}

void	add_nb_ant(char *str)
{
	t_data	*d;

	d = data_init();
	while (str[0] == '#')
	{
		ft_strdel(&str);
		if (get_next_line(FD, &str) <= 0)
			ft_error("ERROR");
	}
	if (!ft_is_number(str))
		ft_error("Fist line isn't a number");
	d->ant = ft_atoi(str);
	d->ant_start = d->ant;
	d->ant_end = 0;
	ft_strdel(&str);
}
