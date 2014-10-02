/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 19:33:58 by garm              #+#    #+#             */
/*   Updated: 2014/10/02 15:49:26 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsock.h>

static void		ftsock_prepare(t_tcpsock *s, t_protoent *proto, int p, int backlog)
{
	int		one;

	one = 1;
	s->ip = NULL;
	s->port = p;
	s->backlog = backlog;
	s->type = FTSOCK_SERVER;
	s->error = FTSOCK_NOERROR;
	if (p == 0)
		s->error = FTSOCK_BAD_PORT;
	if ((s->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		s->error = FTSOCK_SOCKETERROR;
	s->sin.sin_family = AF_INET;
	s->sin.sin_port = htons(p);
	s->sin.sin_addr.s_addr = INADDR_ANY;
	if (setsockopt(s->sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) == -1)
		s->error = FTSOCK_SETSOCK_ERROR;
}

t_tcpsock		*ftsock_create_server(int port, int backlog)
{
	t_tcpsock			*serv;
	struct protoent		*proto;

	proto = getprotobyname("tcp");
	serv = (t_tcpsock *)malloc(sizeof(t_tcpsock));
	ftsock_prepare(serv, proto, port, backlog);
	if (!serv->error)
	{
		if ((bind(serv->sock, (struct sockaddr *)&serv->sin, SINSIZE)) == -1)
			serv->error = FTSOCK_BINDERROR;
	}
	if (!serv->error && (listen(serv->sock, backlog)) == -1)
		serv->error = FTSOCK_LISTENERROR;
	return (serv);
}

t_tcpsock		*ftsock_wait(t_tcpsock *s)
{
	unsigned int	csinsize;
	t_tcpsock		*c;

	c = NULL;
	if (s)
	{
		csinsize = sizeof(struct sockaddr_in);
		c = (t_tcpsock *)malloc(sizeof(t_tcpsock));
		c->ip = NULL;
		c->backlog = 0;
		c->type = FTSOCK_CLIENT;
		c->error = FTSOCK_NOERROR;
		if ((c->sock = accept(s->sock, (t_sockaddr *)&c->sin, &csinsize)) == -1)
			c->error = FTSOCK_ACCEPTERROR;
		c->ip = inet_ntoa(c->sin.sin_addr);
		c->port = ntohs(c->sin.sin_port);
	}
	return (c);
}
