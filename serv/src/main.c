/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 15:56:37 by adebray           #+#    #+#             */
/*   Updated: 2014/10/31 23:55:00 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <serveur.h>
#include <libft.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#include <stdio.h>

int		main(int argc, char **argv)
{
	char ch;
	t_env env;

	while ((ch = getopt(argc, argv, "p:x:y:n:c:")) != -1)
	{
		if (ch == '?')
			;
		else
			ft_fill_env(&env, ch, optarg);
	}

	ft_print_env(&env);

	int sock;
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror ("socket");
		exit (EXIT_FAILURE);
	}
	if (listen(sock, PF_INET) < 0)
	{
		perror ("listen");
		exit (EXIT_FAILURE);
	}

	while (42)
	{
		struct sockaddr *addr;
		int ret1;
		ret1 = accept (sock, addr, sizeof(addr));
	}

	return (0);
}
