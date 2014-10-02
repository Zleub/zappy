/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_serv_close.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/28 23:36:52 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:20:20 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsock.h"

void		ftsock_serv_close(t_serv *s)
{
	t_client	*c;
	t_client	*old;
	
	if (s)
	{
		c = s->clients;
		while (c)
		{
			ftsock_destroy(&(c->tcps));
			ft_strdel(&(c->send_data));
			utils_cbuff_destroy(&(c->recv_cbuf));
			old = c;
			c = c->next;
			ft_memdel((void **)&old);
		}
		ftsock_destroy(&s->tcps);
	}
}

void		ftsock_serv_closeclient(t_serv *s, t_client **c)
{
	if (s && c && *c)
	{
		(*c)->closed = 1;
		FD_SET((*c)->tcps->sock, &(s->write_fds));
	}
}
