/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 15:56:37 by adebray           #+#    #+#             */
/*   Updated: 2014/11/02 16:09:21 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

int					ft_sockinit(t_env *env)
{
	// SIN STRUCT is used for binding a socket to an adress
	// so init
	memset(&env->sin, 0, sizeof(env->sin));
	env->sin.sin_len = sizeof(env->sin);
	env->sin.sin_family = AF_INET;
	env->sin.sin_port = htons(env->port);
	env->sin.sin_addr.s_addr= INADDR_ANY;

	// socket creation
	if ((env->ipv4_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror ("socket");
		return (-1);
	}
	// bind to adress
	if (bind(env->ipv4_socket,
		(struct sockaddr *)&env->sin, sizeof(env->sin)) < 0)
	{
		perror("bind");
		return (-1);
	}
	// listen for incomming connections
	if (listen(env->ipv4_socket, PF_INET) == -1)
	{
		perror("listen");
		return (-1);
	}
	// Because this is unix, sockets are file descriptors
	// To select the fd you wana talk to, you need some groups and groups init:
	FD_ZERO (&env->active_fd_set);
	FD_SET (env->ipv4_socket, &env->active_fd_set);
	return (0);
}

int					main(int argc, char **argv)
{
	char			ch;
	t_env			env;

	// GET OPTION FROM COMMAND LINE
	while ((ch = getopt(argc, argv, "p:x:y:n:c:")) != -1)
	{
		if (ch == '?')
			;
		else
			ft_fill_env(&env, ch, optarg);
	}
	ft_print_env(&env);

	// SOCKETS INITIALIZATION
	if (ft_sockinit(&env) < 0)
		exit (0);
	else
		// SOCKETS LOOP
		ft_sockloop(&env);

	return (0);
}
