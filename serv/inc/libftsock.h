/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftsock.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 16:29:18 by garm              #+#    #+#             */
/*   Updated: 2014/10/02 16:14:58 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSOCK_H
# define LIBFTSOCK_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>

# include "libft.h"
# include "libft_config.h"

# define FTSOCK_BUFFER 4096
# define FTSOCK_MAXBUF ((1024) * (1024) * 8)

# define FT_EOL '\n'
# define DEFAULT_EOT FT_EOL

# define FTSOCK_SERVER 0
# define FTSOCK_CLIENT 1

# define FTSOCK_NOERROR 0
# define FTSOCK_SOCKETERROR 1
# define FTSOCK_BINDERROR 2
# define FTSOCK_LISTENERROR 3
# define FTSOCK_ACCEPTERROR 4
# define FTSOCK_CONNECTERROR 5
# define FTSOCK_MUSTBE_CLIENT 6
# define FTSOCK_MUSTBE_SERVER 7
# define FTSOCK_UNABLE_RESOLVE 8
# define FTSOCK_BAD_PORT 9
# define FTSOCK_SETSOCK_ERROR 10

# define FTSOCK_SOCKETERROR_STR "ftsock: socket() error."
# define FTSOCK_BINDERROR_STR "ftsock: bind() error."
# define FTSOCK_LISTENERROR_STR "ftsock: listen() error."
# define FTSOCK_ACCEPTERROR_STR "ftsock: accept() error."
# define FTSOCK_CONNECTERROR_STR "ftsock: connect() error."
# define FTSOCK_MUSTBE_CLIENT_STR "ftsock error: type must be FTSOCK_CLIENT."
# define FTSOCK_MUSTBE_SERVER_STR "ftsock error: type must be FTSOCK_SERVER."
# define FTSOCK_UNABLE_RESOLVE_STR "ftsock error: Unable to resolve host."
# define FTSOCK_BAD_PORT_STR "ftsock error: Bad port."
# define FTSOCK_SETSOCK_ERROR_STR "ftsock error : setsockopt() error."

# define SINSIZE sizeof(struct sockaddr_in)

# include "libftsock_struct.h"

/*
** Events
*/
void		ftsock_connect_hook(t_serv *s, void (*f)(t_serv *, t_ccom **));
void		ftsock_disconnect_hook(t_serv *s, void (*f)(t_serv *, t_ccom **));
void		ftsock_recv_hook(t_serv *s, void (*f)(t_serv *, t_ccom **, char *));
void		ftsock_timeout_hook(t_serv *s, void (*f)(t_serv *), time_t secs);
void		ftsock_loop_hook(t_serv *s, void (*f)(t_serv *));
void		ftsock_loop(t_serv *s);

/*
** Server (User)
*/
t_serv		*ftsock_serv_multi_client(int port, int backlog);
void		ftsock_serv_close(t_serv *s);
void		ftsock_broadcast(t_serv *s, t_client *c, const char *data);
void		ftsock_broadcast_all(t_serv *s, const char *data);
void		ftsock_serv_closeclient(t_serv *s, t_client **c);

/*
** Server (Internal)
*/
void		ftsock_serv_receive(t_serv *s, t_client **c);
void		ftsock_serv_send(t_serv *s, t_client *c, const char *data);
void		ftsock_serv_write(t_serv *s, t_client **c);

/*
** Client
*/

/*
** ftsock_clients_stack.c
*/
t_client	*ftsock_client_add(t_client *stack, t_sock *tcps);
void		ftsock_client_del(t_client **stack, t_client **todel);

/*
** Circular Buffer
*/
t_cbuff		*utils_cbuff_create(size_t size);
void		utils_cbuff_destroy(t_cbuff **b);
int			utils_cbuff_write(t_cbuff *b, void *data, size_t len);
void		utils_cbuff_bzero(t_cbuff *b);

/*
** ftsock.c
*/
t_sock		*ftsock_create(char type, ...);
void		ftsock_destroy(t_sock **socket);

/*
** ftsock_client.c
*/
t_sock		*ftsock_create_client(char *ip, int port);
void		ftsock_connect(t_sock *s);

/*
** ftsock_server.c
*/
t_sock		*ftsock_create_server(int port, int queue_len);
t_sock		*ftsock_wait(t_sock *serv);

/*
** ftsock_resolve.c
*/
void		ftsock_resolve_host(t_sock *host, char *ip);

/*
** ftsock_error.c
*/
int			ftsock_perror(char error);

#endif
