/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/02 15:02:18 by Arno              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2014/12/09 21:45:05 by adebray          ###   ########.fr       */
=======
/*   Updated: 2014/12/02 22:24:59 by adebray          ###   ########.fr       */
>>>>>>> 8d3dceebbd77af7ae1da7c442d602b8cab411e98
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

// static void			broadcast(int fd, char *buf)
// {
// 	int				len;
// 	t_client_list	*tmp;

// 	len = strlen(buf);
// 	if (!(tmp = manage_client_list(GET, NULL, 0)))
// 		return ;

// 	while (tmp != NULL)
// 	{
// 		if (tmp->elem->fd != fd)
// 			send(tmp->elem->fd, buf, len, 0);
// 		tmp = tmp->next;
// 	}
// }

t_client			*ft_get_client_by_fd(int fd)
{
	t_client_list	*head;

	head = manage_client_list(GET, NULL, 0);
	while (head)
	{
		if (head->elem->fd == fd)
			return (head->elem);
	}
	return (NULL);
}

// static char			*ft_add_endline(char *str)
// {
// 	char			*ret;
// 	char			*tmp;

// 	if (!(ret = (char *)malloc(sizeof(char) * (strlen(str) + 2))))
// 		return (NULL);
// 	tmp = ret;
// 	while (*str)
// 	{
// 		*tmp = *str;
// 		tmp += 1;
// 		str += 1;
// 	}
// 	*tmp = '\n';
// 	tmp += 1;
// 	*tmp = '\0';
// 	return (ret);
// }

// static void			ft_get_team(t_client *client, char *buf)
// {
// 	t_team_list		*team;

// 	team = manage_team_list(GET, NULL);
// 	while (team && strcmp(team->elem, buf))
// 		team = team->next;
// 	if (team == NULL)
// 		send(client->fd, "ko\n", 3, 0);
// 	else
// 	{
// 		send(client->fd, "ok\n", 3, 0);
// 		send(client->fd, ft_add_endline(ft_itoa(team->slots)), strlen(ft_itoa(team->slots)) + 1, 0);
// 	}

// }

// static void			ft_read_bystate(int fd, char *buf)
// {
// 	t_client		*client;

// 	client = ft_get_client_by_fd(fd);
// 	if (client->state == LOBBY)
// 		ft_get_team(client, buf);
// }

static void				ft_trim(char *str)
{
	int					i;

	i = strlen(str) - 1;
	while (str[i] == '\n')
	{
		str[i] = '\0';
		i -= 1;
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
		ft_trim(buf);
		printf("SRV from %d: <%s>\n", fd, buf);
		// ft_read_bystate(fd, buf);
		// broadcast(fd, buf);
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
	FD_SET (clientfd, &env->active_fd_set);

	send(clientfd, "BIENVENUE\n", 10, 0);
	manage_client(GET)->state = LOBBY;

	printf("+ new client:\n");
	// manage_client_list(PRINT, NULL, 0);
}

static void			ft_sockget(t_env *env, int fd)
{
	if (fd == env->ipv4_socket)
		ft_newclient(env);
	else
	{
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

	while (42)
	{
		read_fd_set = env->active_fd_set;
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			perror ("select");
			exit (EXIT_FAILURE);
		}
		fd = 0;
		while (fd < FD_SETSIZE)
		{
			if (FD_ISSET (fd, &read_fd_set))
				ft_sockget(env, fd);
			fd += 1;
		}
	}
}
