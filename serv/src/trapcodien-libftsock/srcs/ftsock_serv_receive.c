/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_serv_receive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/30 12:22:13 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:20:18 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsock.h"

static size_t		utils_memlenc(const char *s, char c, size_t len)
{
	size_t		i;

	i = 0;
	while (s && s[i] && i < len && s[i] != c)
		i++;
	return (i);
}

static void			utils_str_truncate_begin(char *buffer, size_t start)
{
	char	tmp[FTSOCK_BUFFER];
;
	ft_bzero(tmp, FTSOCK_BUFFER);
	ft_strcpy(tmp, buffer + start);
	ft_bzero(buffer, FTSOCK_BUFFER);
	ft_strcpy(buffer, tmp);
}

static void			receive_handle(t_serv *s, t_client **c)
{
	char		*tmp;

	tmp = ft_strdup((*c)->recv_cbuf->data);
	if (s->recv_handle)
		s->recv_handle(s, c, tmp);
	ft_strdel(&tmp);
}

void				ftsock_serv_receive(t_serv *s, t_client **c)
{
	size_t		len_cpy;
	char		*buffer;

	if (!s || !c || !*c)
		return ;
	buffer = (*c)->recv_buf;
	len_cpy = utils_memlenc(buffer, s->eot, FTSOCK_BUFFER);
	if (len_cpy == 0 && *buffer != s->eot)
		return ;
	if (len_cpy >= FTSOCK_BUFFER || *(buffer + len_cpy) != s->eot)
		utils_cbuff_write((*c)->recv_cbuf, buffer, len_cpy);
	else if (*(buffer + len_cpy) == s->eot)
	{
		utils_cbuff_write((*c)->recv_cbuf, buffer, len_cpy);
		receive_handle(s, c);
		if (!s->tcps || !c || !*c)
			return ;
		utils_cbuff_bzero((*c)->recv_cbuf);
		if (*(buffer + len_cpy + 1) != 0)
		{
			utils_str_truncate_begin(buffer, len_cpy + 1);
			ftsock_serv_receive(s, c);
		}
	}
	ft_bzero(buffer, FTSOCK_BUFFER);
}
