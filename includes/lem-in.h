/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 21:12:53 by ebaudet           #+#    #+#             */
/*   Updated: 2014/02/18 21:12:53 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define FD		1
# define START	1
# define END	2

typedef struct			s_con
{
	struct s_room		*room;
	struct t_con		*next;
}						t_con;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y
	struct s_room		*next;
	t_con				*con;
}						t_room;

typedef struct			s_data
{
	t_room				*start;
	t_room				*end;
	t_room				**list_room;
}						t_data;

/*
** error.c
*/
void			ft_error(char *str);

/*
** data.c
*/
t_data			*data_init(void);

/*
** parser.c
*/
int				pars_in(void);
int				add_position(int fd, int pos);
int				add_room(char **room, int pos);
int				add_pipe(char **pipe);

/*
** graph.c
*/
t_list_node		*create_node(int v);
t_graph			*create_graph(int n);

#endif /* !LEM_IN_H */
