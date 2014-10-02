/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftsock_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/28 01:04:34 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:17:08 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSOCK_STRUCT_H
# define LIBFTSOCK_STRUCT_H

typedef struct sockaddr		t_sockaddr;
typedef struct protoent		t_protoent;

typedef struct s_server		t_serv;
typedef struct s_client		t_ccom;
typedef struct s_tcpsock	t_sock;

typedef struct				s_cbuff
{
	void					*data;
	size_t					size;
	long					offset;
}							t_cbuff;

typedef struct				s_tcpsock
{
	struct sockaddr_in		sin;
	int						sock;
	char					*ip;
	int						port;
	int						backlog;
	char					type;
	char					error;
}							t_tcpsock;

typedef struct				s_client
{
	t_tcpsock				*tcps;
	struct s_client			*next;
	void					*user_data;
	int						closed;
	char					recv_buf[FTSOCK_BUFFER];
	t_cbuff					*recv_cbuf;
	char					send_buf[FTSOCK_BUFFER + 1];
	char					*send_data;
	size_t					send_offset;
}							t_client;

typedef struct				s_server
{
	t_tcpsock				*tcps;
	void					*user_data;
	t_client				*clients;
	fd_set					read_fds;
	fd_set					write_fds;
	int						higher_fd;
	char					eot;
	void					(*connect_handle)(t_serv *, t_ccom **);
	void					(*disconnect_handle)(t_serv *, t_ccom **);
	void					(*recv_handle)(t_serv *, t_ccom **, char *);
	void					(*timeout_handle)(t_serv *);
	void					(*loop_handle)(t_serv *);
	struct timeval			tv;
}							t_server;

#endif
