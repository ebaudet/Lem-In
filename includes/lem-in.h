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
# define FD		0
# define START	1
# define END	2

typedef struct			s_pipe
{
	struct s_room		*room;
	struct s_pipe		*next;
}						t_pipe;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	struct s_room		*next;
	t_pipe				*pipe;
}						t_room;

typedef struct			s_data
{
	t_room				*start;
	t_room				*end;
	t_room				**list_room;
	int					ant;
	int					ant_start;
	int					ant_end;
}						t_data;

/*
** error.c
*/
void			ft_error(char *str);

/*
** ft_is_number.c
*/
int				ft_is_number(char *str);

/*
** data.c
*/
t_data			*data_init(void);
void			add_nb_ant(char *str);

/*
** parser.c
*/
int				parse_entry(void);
int				add_position(int fd, int pos);
int				add_room(char **room, int pos);
int				add_pipe(char **pipe);

/*
** room.c
*/
t_room			*new_room(char *name, int x, int y);
t_room			*list_add_room(char *name, int x, int y);

/*
** pipe.c
*/
t_pipe			*pipe_new(t_room *room);
int				list_add_pipe(char *room1, char *room2);
void			pipe_room(t_room *room, t_room *pipe);

/*
** tools.c
*/
int				free_tab(char **tab);

#endif /* !LEM_IN_H */
