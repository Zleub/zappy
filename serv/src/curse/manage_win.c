/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/15 14:55:47 by adebray           #+#    #+#             */
/*   Updated: 2014/10/02 16:50:38 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curse.h>

t_win		*create_win(t_wintab *array)
{
	t_win	*new;

	new = newwin(array[0], array[1], array[2], array[3]);
	manage_win_list(ADD, new);
	wrefresh(new);
	return (new);
}

t_win		*create_boxed_win(t_wintab *array)
{
	t_win	*new;

	new = newwin(array[0], array[1], array[2], array[3]);
	manage_win_list(ADD, new);
	box(new, 0, 0);
	wrefresh(new);
	return (new);
}

void		print_win(t_win *ptr)
{
	ft_printf("print_win\n");
	ft_printf("ptr: %p", ptr);
}

void		print_win_fd(t_win *ptr, int fd)
{
	char	*content;

	asprintf(&content, "print_win_fd:\nwin: %p\n", ptr);
	write(fd, content, ft_strlen(content));
	free (content);
}

void		refresh_win(t_win *win)
{
	wrefresh(win);
}

void		destroy_win(t_win *win)
{
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(win);
	delwin(win);
}

t_win		*manage_win(int macro, t_wintab *array)
{
	static t_win	*ptr;

	if (macro == GET)
		return (ptr);
	else if (macro == NEW_B)
	{
		ptr = create_boxed_win(array);
		return (ptr);
	}
	else if (macro == NEW)
	{
		ptr = create_win(array);
		return (ptr);
	}
	else if (macro == PRINT)
		print_win(ptr);
	else if (macro == FRESH)
		refresh_win(ptr);
	else if (macro == DELETE)
		destroy_win(ptr);
	else
		ft_printf("Useless call to manage_win\n");
	return (NULL);
}
