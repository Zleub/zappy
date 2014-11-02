/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/02 15:02:18 by Arno              #+#    #+#             */
/*   Updated: 2014/11/02 18:21:32 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

static void			broadcast(int fd, char *buf)
{
	int				len;
	t_client_list	*tmp;

	len = strlen(buf);
	if (!(tmp = manage_client_list(GET, NULL, 0)))
		return ;

	while (tmp != NULL)
	{
		if (tmp->elem->fd != fd)
			send(tmp->elem->fd, buf, len, 0);
		tmp = tmp->next;
	}
}

static int			ft_read(int fd)
{
	char			buf[MAXMSG];
	int				i;

	bzero(buf, MAXMSG);
	i = recv(fd, buf, MAXMSG, 0);
	if (i < 0)
	{
		perror ("read");
		exit (EXIT_FAILURE);
	}
	else if (i == 0)
		return -1;
	else
	{
		printf("SRV from %d: %s", fd, buf);
		broadcast(fd, buf);
	}
	return (0);
}

static void			ft_newclient(t_env *env)
{
	unsigned int	size;
	int				clientfd;

	size = sizeof(struct sockaddr_in);
	if ((clientfd = accept (env->ipv4_socket,
		(struct sockaddr *)&manage_client(GET)->sin, &size)) < 0)
	{
		perror("accept");
		exit (0);
	}
	manage_client(NEW);
	manage_client(GET)->fd = clientfd;
	send(clientfd, "BIENVENUE\n", 10, 0);
	FD_SET (clientfd, &env->active_fd_set);
	printf("+ new client:\n");
	manage_client_list(PRINT, NULL, 0);
}

static void			ft_sockget(t_env *env, int fd)
{
	if (fd == env->ipv4_socket)
		ft_newclient(env);
	else
	{
		/* Data arriving on an already-connected socket. */
		if (ft_read(fd) < 0)
		{
			close (fd);
			manage_client_list(REMOVE, NULL, fd);
			FD_CLR (fd, &env->active_fd_set);
			printf("- client leave:\n");
			manage_client_list(PRINT, NULL, 0);

		}
	}
}

int					ft_sockloop(t_env *env)
{
	int				fd;
	fd_set			read_fd_set;


	// SET TIMEOUT
	while (42)
	{
		read_fd_set = env->active_fd_set;
		// SELECT the FD in the read && write fd set 
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			perror ("select");
			exit (EXIT_FAILURE);
		}
		fd = 0;
		while (fd < FD_SETSIZE)
		{
			if (FD_ISSET (fd, &read_fd_set))
				// DO WANT U HAVE TO WITH EACH FD AVAILABLE TO READ OR WRITE
				ft_sockget(env, fd);
			fd += 1;
		}
	}
}
