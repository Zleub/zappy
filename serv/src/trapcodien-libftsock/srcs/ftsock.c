/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 19:14:59 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:20:27 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsock.h"

t_tcpsock	*ftsock_create(char type, ...)
{
	t_tcpsock	*socket;
	va_list		ap;
	char		*ip;
	int			port;

	socket = NULL;
	va_start(ap, type);
	if (type == FTSOCK_SERVER)
	{
		port = va_arg(ap, int);
		socket = ftsock_create_server(port, va_arg(ap, int));
	}
	else if (type == FTSOCK_CLIENT)
	{
		ip = va_arg(ap, char *);
		socket = ftsock_create_client(ip, va_arg(ap, int));
	}
	va_end(ap);
	return (socket);
}

void		ftsock_destroy(t_tcpsock **socket)
{
	if (socket)
	{
		close((*socket)->sock);
		free((void *)*socket);
		*socket = NULL;
	}
}
