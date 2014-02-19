/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 21:40:39 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/18 21:40:39 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"

t_list_node		*create_node(int v)
{
	t_list_node	*new;

	if ((new = (t_list_node *)malloc(sizeof(t_list_node))) == 0)
		ft_error("error malloc new node");
	new->vertex = v;
	new->next = NULL;
	return (new);
}

t_graph			*create_graph(int n)
{
	int			i;
	t_graph		*graph;

	if ((graph = (t_graph *)malloc(sizeof(t_graph))) == 0)
		ft_error("error malloc new graph");
	graph->num_vertice = n;
	if ((graph->list_array = (t_list *)malloc(sizeof(t_list))) == 0)
		ft_error("error malloc new list array");
}