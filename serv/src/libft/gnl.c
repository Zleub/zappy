/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/13 22:21:30 by tcharlat          #+#    #+#             */
/*   Updated: 2014/08/07 11:24:45 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

char				*ft_strcatloc(char *str1, char*str2)
{
	char			*save;
	char			*ret;

	ret = (char*)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)) + 1);
	save = ret;
	if (str1)
	{
		while (*str1)
			*ret++ = *str1++;
	}
	if (str2)
	{
		while (*str2)
			*ret++ = *str2++;
	}
	*ret = '\0';
	return (save);
}

int					get_next_line(int fd, char **line)
{
	int				ret;
	char			tmp[2];

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
