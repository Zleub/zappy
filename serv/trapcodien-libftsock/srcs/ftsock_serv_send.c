/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_serv_send.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/28 01:17:05 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:20:17 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsock.h"

void		ftsock_serv_write(t_serv *s, t_client **client_ptr)
{
	size_t		i;
	t_client	*c;

	if (!s || !client_ptr || !*client_ptr)
		return ;
	c = *client_ptr;
	i = 0;
	while (i < FTSOCK_BUFFER && c->send_data && c->send_data[c->send_offset])
	{
		c->send_buf[i] = c->send_data[c->send_offset];
		c->send_offset++;
		i++;
	}
	ft_putstr_fd(c->send_buf, c->tcps->sock);
	ft_bzero(c->send_buf, FTSOCK_BUFFER);
	if (!c->send_data || !c->send_data[c->send_offset])
	{
		ft_strdel(&(c->send_data));
		c->send_offset = 0;
		FD_CLR(c->tcps->sock, &(s->write_fds));
		if (c->closed)
			ftsock_client_del(&(s->clients), client_ptr);
	}
}

void			ftsock_serv_send(t_serv *s, t_client *c, const char *data)
{
	char	eot[2];
	char	*send_data;

	if (!s || !c || !data || !s->tcps)
		return ;
	eot[0] = s->eot;
	eot[1] = 0;
	send_data = c->send_data;
	c->send_data = ft_strjoin(send_data, data);
	ft_strdel(&send_data);
	send_data = c->send_data;
	c->send_data = ft_strjoin(send_data, eot);
	ft_strdel(&send_data);
	if (c->send_data)
		FD_SET(c->tcps->sock, &(s->write_fds));
}

void			ftsock_broadcast(t_serv *s, t_client *c, const char *data)
{
	t_client	*cursor;

	if (s && c && data && s->tcps)
	{
		cursor = s->clients;
		while (cursor)
		{
			if (cursor->tcps->sock != c->tcps->sock)
				ftsock_serv_send(s, cursor, data);
			cursor = cursor->next;
		}
	}
}

void			ftsock_broadcast_all(t_serv *s, const char *data)
{
	t_client	*c;

	if (s && data && s->tcps)
	{
		c = s->clients;
		while (c)
		{
			ftsock_serv_send(s, c, data);
			c = c->next;
		}
	}
}
