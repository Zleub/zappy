/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_serv_multi_client.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/28 00:49:34 by garm              #+#    #+#             */
/*   Updated: 2014/10/02 15:49:05 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsock.h>

t_serv						*ftsock_serv_multi_client(int port, int backlog)
{
	t_tcpsock	*tcps;
	t_serv		*server;

	server = ft_memalloc(sizeof(t_serv));
	if (!server)
		return (NULL);
	tcps = ftsock_create(FTSOCK_SERVER, port, backlog);
	server->tcps = tcps;
	server->user_data = NULL;
	server->clients = NULL;
	FD_ZERO(&server->read_fds);
	FD_ZERO(&server->write_fds);
	server->higher_fd = 0;
	server->eot = DEFAULT_EOT;
	server->connect_handle = NULL;
	server->disconnect_handle = NULL;
	server->recv_handle = NULL;
	server->timeout_handle = NULL;
	server->loop_handle = NULL;
	return (server);
}

