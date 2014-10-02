/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wintab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/15 19:39:32 by adebray           #+#    #+#             */
/*   Updated: 2014/10/02 15:37:24 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curse.h>

void			print_wintab_fd(t_wintab *array, int fd)
{
	char	*content;

	asprintf(&content, "print_wintab_fd:\narray: %p\n", array);
	write(fd, content, ft_strlen(content));
	free (content);
}

t_wintab		*create_wintab(int i, int j, int x, int y)
{
	t_wintab	*array;

	if (!(array = (t_wintab*)malloc(sizeof(t_wintab) * 4)))
		return (NULL);
	array[0] = i;
	array[1] = j;
	array[2] = x;
	array[3] = y;
	manage_wintab_list(ADD, array);
	return (array);
}

void			destroy_wintab(t_wintab *ptr)
{
	free(ptr);
	ptr = NULL;
}

t_wintab		*manage_wintab(int macro, t_wintab *array)
{
	static t_wintab	*ptr;

	if (macro == GET)
		return (ptr);
	else if (macro == SET)
	{
		if (!ptr)
			ptr = array;
		else
			ft_printf("Ptr already set\n");
	}
	else
		ft_printf("Useless call to manage_wintab\n");
	return (NULL);
}
