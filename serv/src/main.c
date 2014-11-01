/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 15:56:37 by adebray           #+#    #+#             */
/*   Updated: 2014/11/01 15:53:14 by adebray          ###   ########.fr       */
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
	if (bind(env->ipv4_socket, (struct sockaddr *)&env->sin, sizeof(env->sin)) < 0)
	{
		perror("bind");
		return (-1);
	}
	if (listen(env->ipv4_socket, PF_INET) == -1)
	{
		perror("listen");
		return (-1);
	}
	return (0);
}

int					ft_sockloop(t_env *env)
{
	int				clientfd;
	unsigned int	size;

	size = sizeof(struct sockaddr_in);
	while (42)
	{
		manage_client(NEW);
		if ((clientfd = accept (env->ipv4_socket, (struct sockaddr *)&manage_client(GET)->sin, &size)) < 0)
		{
			perror("accept");
			exit (0);
		}
		else
		{
			manage_client_list(PRINT, NULL);
		}
	}
}

int					main(int argc, char **argv)
{
	char			ch;
	t_env			env;

	while ((ch = getopt(argc, argv, "p:x:y:n:c:")) != -1)
	{
		if (ch == '?')
			;
		else
			ft_fill_env(&env, ch, optarg);
	}

	ft_print_env(&env);
	if (ft_sockinit(&env) < 0)
		exit (0);
	else
		ft_sockloop(&env);

	return (0);
}
