/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 19:15:51 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:20:26 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsock.h"

t_tcpsock	*ftsock_create_client(char *ip, int port)
{
	t_tcpsock			*client;
	struct protoent		*proto;

	proto = getprotobyname("tcp");
	client = (t_tcpsock *)malloc(sizeof(t_tcpsock));
	client->ip = ip;
	client->port = port;
	client->backlog = 0;
	client->type = FTSOCK_CLIENT;
	client->error = FTSOCK_NOERROR;
	if (port == 0)
		client->error = FTSOCK_BAD_PORT;
	if ((client->sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		client->error = FTSOCK_SOCKETERROR;
	client->sin.sin_family = AF_INET;
	client->sin.sin_port = htons(port);
	ftsock_resolve_host(client, ip);
	return (client);
}

void		ftsock_connect(t_tcpsock *s)
{
	if (s && !s->error)
	{
		if (s->type == FTSOCK_CLIENT)
		{
			if ((connect(s->sock, (struct sockaddr *)&s->sin, SINSIZE) == -1))
				s->error = FTSOCK_CONNECTERROR;
		}
		else
			s->error = FTSOCK_MUSTBE_CLIENT;
	}
}
