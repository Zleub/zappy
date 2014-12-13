/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/13 22:21:30 by tcharlat          #+#    #+#             */
/*   Updated: 2014/11/21 21:37:25 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <stdio.h>

char		*ft_strcatloc(char *str1, char *str2)
{
	char	*array[4];

	array[1] = (char*)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)) + 1);
	array[0] = array[1];
	array[2] = str1;
	array[3] = str2;
	if (str1)
	{
		while (*str1)
			*array[1]++ = *str1++;
	}
	if (str2)
	{
		while (*str2)
			*array[1]++ = *str2++;
	}
	*array[1] = '\0';
	free(array[2]);
	return (array[0]);
}

int			get_next_line(int fd, char **line)
{
	int		ret;
	char	tmp[2];

	*line = NULL;
	tmp[1] = '\0';
	while ((ret = read(fd, tmp, 1)))
	{
		if (tmp[0] == '\n' || ret == 0)
			return (ret);
		else
			*line = ft_strcatloc(*line, tmp);
	}
	return (ret);
}
