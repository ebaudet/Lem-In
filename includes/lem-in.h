/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 21:12:53 by ebaudet           #+#    #+#             */
/*   Updated: 2014/03/23 04:27:51 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

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
	char				path;
}						t_room;

typedef struct			s_path
{
	t_room				*room;
	struct s_path		*next;
	struct s_path		*prev;
	int					ant;
	int					this_ant;
}						t_path;

typedef struct			s_data
{
	t_room				*start;
	t_room				*end;
	t_room				**list_room;
	t_path				*path;
	int					ant;
	int					ant_start;
	int					ant_end;
	int					nb_room;
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
void			add_nb_ant(void);

/*
** parser.c
*/
int				parse_entry(void);
int				add_position(char **line, int fd, int pos);
int				add_room(char **room, int pos);
int				add_pipe(char **pipe);

/*
** room.c
*/
t_room			*new_room(char *name, int x, int y);
t_room			*list_add_room(char *name, int x, int y);
void			count_room(void);

/*
** pipe.c
*/
t_pipe			*pipe_new(t_room *room);
int				list_add_pipe(char *room1, char *room2);
void			pipe_room(t_room *room, t_room *pipe);

/*
** tools.c
*/
int				free_tab(char ***tab);

/*
** print.c
*/
void			print_room(void);
void			print_pipe(void);
void			print_lemin(int num_lemin, char *room, int i);

/*
** path.c
*/
t_path			*new_path(t_path *prev, t_room *room, t_path *next, int ant);
void			add_end_path(t_data *d, t_room *room);
int				delete_last_path(t_data *d);

/*
** find_path.c
*/
int				search_end(t_room *pos, t_data *d);
void			find_path(t_data *d);
int				find_good_node(t_room **scout, int find, t_data *d);

/*
** follow_path.c
*/
void			follow_path(t_data *d);
void			in_node(t_path *tmp, int *new_lemin, int *i, t_data *d);

#endif /* !LEM_IN_H */
