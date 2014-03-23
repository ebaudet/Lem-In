/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 21:12:22 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/23 20:16:33 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <unistd.h>

int		main(void)
{
	t_data		*d;

	d = data_init();
	parse_entry();
	if (!d->start || !d->end || d->ant <= 0)
		ft_error("ERROR4");
	print_room();
	print_pipe();
	ft_putchar('\n');

	
	find_path(d);
	follow_path(d);

	
	sleep(500);
	return (0);
}
