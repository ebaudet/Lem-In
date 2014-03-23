/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/20 00:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/23 02:55:31 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"
#include "libft.h"

int		free_tab(char ***tab)
{
	int		i;

	i = -1;
	if (tab && (*tab))
		return (0);
	while (*tab[++i])
		ft_strdel(&(*tab[i]));
	free(*tab);
	*tab = NULL;
	return (0);
}
