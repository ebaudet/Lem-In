/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 21:12:22 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/18 21:12:22 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		main(void)
{
	t_data		*d;

	d = data_init();
	parse_entry();
	if (!d->start || !d->end)
		ft_error("ERROR");
	find_path(d);
	print_room();
	print_pipe();
	ft_putchar('\n');
	follow_path(d);
	return (0);
}
