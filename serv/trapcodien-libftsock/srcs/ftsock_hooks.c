/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/28 00:59:03 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:20:23 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsock.h"

void		ftsock_connect_hook(t_serv *s, void (*f)(t_serv *, t_ccom **))
{
	if (s)
		s->connect_handle = f;
}

void		ftsock_disconnect_hook(t_serv *s, void (*f)(t_serv *, t_ccom **))
{
	if (s)
		s->disconnect_handle = f;
}

void		ftsock_recv_hook(t_serv *s, void (*f)(t_serv *, t_ccom **, char *))
{
	if (s)
		s->recv_handle = f;
}

void		ftsock_timeout_hook(t_serv *s, void (*f)(t_serv *s), time_t secs)
{
	if (s)
	{
		s->tv.tv_sec = secs;
		s->tv.tv_usec = 0;
		s->timeout_handle = f;
	}
}

void		ftsock_loop_hook(t_serv *s, void(*f)(t_serv *s))
{
	if (s)
		s->loop_handle = f;
}
