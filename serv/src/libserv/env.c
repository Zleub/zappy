/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/31 11:22:13 by Arno              #+#    #+#             */
/*   Updated: 2014/11/02 19:46:09 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

void	ft_print_env(t_env *env)
{
	printf("port->%d\n", env->port);
	printf("x->%d\n", env->x);
	printf("y->%d\n", env->y);
	printf("teams->%p\n", env->teams);
	manage_team_list(PRINT, NULL);
	printf("clientmax->%d\n", env->clientmax);
}

void	ft_fill_env(t_env *env, char ch, char *optarg)
{
	if (ch == 'p')
		env->port = ft_atoi(optarg);
	else if (ch == 'x')
		env->x = ft_atoi(optarg);
	else if (ch == 'y')
		env->y = ft_atoi(optarg);
	else if (ch == 'n')
	{
		while (optarg[0] != '-' && strncmp(optarg, "PATH", 4))
		{
			new_team_list(optarg);
			optarg += strlen(optarg) + 1;
		}
		env->teams = manage_team_list(GET, NULL);
	}
		// MULTTIPLE NAMES HERE
	else if (ch == 'c')
	{
		env->clientmax = ft_atoi(optarg);
		if (env->clientmax == 0)
			env->clientmax = 10;
		// INCORRECT
	}
}
