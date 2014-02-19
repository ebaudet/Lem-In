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

#include "lem-in.h"

t_data	*data_init(void)
{
	static t_data	*d = NULL;

	if (!d)
	{
		if ((d = (t_data *)malloc(sizeof(t_data))) == 0)
			ft_error("error malloc data");
		d->start = NULL;
		d->end = NULL;
		d->list_room = NULL;
	}
	return (d);
}
