/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wintab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/15 19:39:32 by adebray           #+#    #+#             */
/*   Updated: 2014/07/17 09:34:59 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curse.h>

void		print_wintab_fd(WINTAB *array, int fd)
{
	char	*content;

	asprintf(&content, "print_wintab_fd:\narray: %p\n", array);
	write(fd, content, ft_strlen(content));
	free (content);
}

WINTAB		*create_wintab(int i, int j, int x, int y)
{
	WINTAB	*array;

	if (!(array = (WINTAB*)malloc(sizeof(WINTAB) * 4)))
		return (NULL);
	array[0] = i;
	array[1] = j;
	array[2] = x;
	array[3] = y;
	manage_wintab_list(ADD, array);
	return (array);
}

void		destroy_wintab(WINTAB *ptr)
{
	free(ptr);
	ptr = NULL;
}

WINTAB		*manage_wintab(int macro, WINTAB *array)
{
	static WINTAB	*ptr;

	if (macro == GET)
		return (ptr);
	else if (macro == SET)
	{
		if (!ptr)
			ptr = array;
		else
			ft_printf("Ptr already set\n");
	}
	// else if (macro == ADD)
		// add_wintab_list(ptr, array);
	else
		ft_printf("Useless call to manage_wintab\n");
	return (NULL);
}
