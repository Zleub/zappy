/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/16 02:11:30 by adebray           #+#    #+#             */
/*   Updated: 2014/10/02 15:27:12 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSE_H
# define CURSE_H

# include <ncurses.h>
# include <ft_printf.h>
# include <stdlib.h>
# include <fcntl.h>
# include <libft.h>
# include <sys/ioctl.h>

enum						e_manage
{
	GET, SET, NEW, ADD, LOAD, PRINT, FRESH, DELETE, NEW_B, ERROR
};

typedef WINDOW				t_win;

/*
** WINDOW type form ncurses
*/

typedef struct				s_win_list
{
	t_win					*win;
	struct s_win_list		*next;
}							t_win_list;

typedef int					t_wintab;

/*
**	t_wintab is a basic param for t_win creation as
**	t_wintab[0] = height
**	t_wintab[1] = width
**	t_wintab[2] = x
**	t_wintab[3] = y
*/

typedef struct				s_wintab_list
{
	t_wintab				*array;
	struct s_wintab_list	*next;
}							t_wintab_list;

t_win						*manage_ncurses(int macro);
int							lines_center();
int							cols_center();

t_win_list					*manage_win_list(int macro, t_win *object);

t_win						*manage_win(int macro, t_wintab *array);
t_win						*create_win(t_wintab *array);
void						print_win(t_win *ptr);
void						print_win_fd(t_win *ptr, int fd);
void						refresh_win(t_win *win);
void						destroy_win(t_win *win);

t_wintab_list				*manage_wintab_list(int macro, t_wintab *array);

t_wintab					*manage_wintab(int macro, t_wintab *array);
t_wintab					*create_wintab(int i, int j, int x, int y);
void						print_wintab_fd(t_wintab *array, int fd);
void						destroy_wintab(t_wintab *ptr);

#endif
