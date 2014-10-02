/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/28 01:18:02 by garm              #+#    #+#             */
/*   Updated: 2014/10/02 15:48:44 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsock.h>

static void		new_client(t_serv *s)
{
	t_tcpsock		*new_tcps;

	new_tcps = ftsock_wait(s->tcps);
	if (new_tcps->sock > s->higher_fd)
		s->higher_fd = new_tcps->sock;
	s->clients = ftsock_client_add(s->clients, new_tcps);
	if (s->connect_handle)
		s->connect_handle(s, &(s->clients));
}

static void		del_client(t_serv *s, t_client *todel)
{
	int			new_higher_fd;
	int			fd_todel;
	t_client	*c;

	if (s->disconnect_handle)
		s->disconnect_handle(s, &todel);
	new_higher_fd = -1;
	fd_todel = todel->tcps->sock;
	ftsock_client_del(&(s->clients), &todel);
	if (!s->clients)
		s->higher_fd = s->tcps->sock;
	else if (fd_todel == s->higher_fd)
	{
		c = s->clients;
		while (c)
		{
			if (new_higher_fd < c->tcps->sock)
				new_higher_fd = c->tcps->sock;
			c = c->next;
		}
		s->higher_fd = new_higher_fd;
	}
}

static void		select_clients(t_serv *s)
{
	t_client	*c;

	c = s->clients;
	while (c)
	{
		if (FD_ISSET(c->tcps->sock, &(s->read_fds)))
		{
			if ((read(c->tcps->sock, c->recv_buf, FTSOCK_BUFFER)) <= 0)
			{
				del_client(s, c);
				return ;
			}
			else
				ftsock_serv_receive(s, &c);
		}
		else if (FD_ISSET(c->tcps->sock, &(s->write_fds)))
			ftsock_serv_write(s, &c);
		if (!s->tcps || !c)
			return ;
		c = c->next;
	}
}

static void		init_fds(t_serv *s)
{
	t_client	*c;

	FD_ZERO(&s->read_fds);
	FD_SET(s->tcps->sock, &s->read_fds);
	c = s->clients;
	while (c)
	{
		FD_SET(c->tcps->sock, &s->read_fds);
		c = c->next;
	}
	if (s->loop_handle)
		s->loop_handle(s);
}

void			ftsock_loop(t_serv *s)
{
	int					ret;
	int					h_fd;
	struct timeval		*tv;

	if (!s)
		return ;
	tv = NULL;
	if (s->timeout_handle)
		tv = &(s->tv);
	s->higher_fd = s->tcps->sock;
	FD_ZERO(&s->write_fds);
	while (s->tcps)
	{
		init_fds(s);
		h_fd = s->higher_fd + 1;
		ret = select(h_fd, &s->read_fds, &s->write_fds, NULL, tv);
		if (FD_ISSET(s->tcps->sock, &(s->read_fds)))
			new_client(s);
		else if (ret == 0)
			s->timeout_handle(s);
		else
			select_clients(s);
	}
	ft_memdel((void **)&s);
}
