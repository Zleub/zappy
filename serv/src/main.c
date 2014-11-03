/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 15:56:37 by adebray           #+#    #+#             */
/*   Updated: 2014/11/03 04:17:23 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

int					ft_sockinit(t_env *env)
{
	memset(&env->sin, 0, sizeof(env->sin));
	env->sin.sin_len = sizeof(env->sin);
	env->sin.sin_family = AF_INET;
	env->sin.sin_port = htons(env->port);
	env->sin.sin_addr.s_addr= INADDR_ANY;

	if ((env->ipv4_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror ("socket");
		return (-1);
	}
	if (bind(env->ipv4_socket,
		(struct sockaddr *)&env->sin, sizeof(env->sin)) < 0)
	{
		perror("bind");
		return (-1);
	}
	if (listen(env->ipv4_socket, PF_INET) == -1)
	{
		perror("listen");
		return (-1);
	}
	FD_ZERO (&env->active_fd_set);
	FD_SET (env->ipv4_socket, &env->active_fd_set);
	return (0);
}

void				ft_usage(void)
{
	printf("Usage: ./serveur [--strict] [-xypct option] [-n teamname [teamname] ...]\n");
	exit (0);
}

int					main(int argc, char **argv)
{
	t_env			*env;
	char			ch;

	ft_manage_env(INIT);
	env = ft_manage_env(GET);
	while ((ch = getopt(argc, argv, "p:x:y:n:c:")) != -1)
	{
		if (ch == '?')
			ft_usage();
		else
		{
			env->this_char = ch;
			env->this_str = optarg;
			ft_manage_env(FILL);
		}
	}
	if (env->port < 1024)
	{
		printf("port must be above 1024\n");
		exit (0);
	}
	ft_manage_env(PRINT);
	if (ft_sockinit(env) < 0)
		exit (0);
	else
		ft_sockloop(env);
	return (0);
}
