/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_curse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/15 14:55:19 by adebray           #+#    #+#             */
/*   Updated: 2014/10/02 15:29:07 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curse.h>

int			cols_center(char *str)
{
	return ((COLS - ft_strlen(str)) / 2);
}

int			lines_center(void)
{
	return (LINES / 2);
}

t_win		*manage_ncurses(int macro)
{
	int				fd;
	static t_win	*main_win;

	if (macro == GET)
		return (main_win);
	else if (macro == NEW)
	{
		if (!(main_win = initscr()))
		{
			fd = open("debug", O_CREAT | O_TRUNC | O_WRONLY, 0755);
			write(fd, "Error initialising ncurses.\n", 28);
			close(fd);
			exit(0);
		}
		curs_set(0);
	}
	else
		ft_printf("Useless call to manage_ncurses\n");
	return (NULL);
}
