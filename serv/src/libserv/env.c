/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/31 11:22:13 by Arno              #+#    #+#             */
/*   Updated: 2014/11/01 15:13:17 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

void	ft_print_env(t_env *env)
{
	printf("port->%d\n", env->port);
	printf("x->%d\n", env->x);
	printf("y->%d\n", env->y);
	printf("name->%s\n", env->name);
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
		env->name = ft_strdup(optarg);
		// MULTTIPLE NAMES HERE
	else if (ch == 'c')
	{
		env->clientmax = ft_atoi(optarg);
		if (env->clientmax == 0)
			env->clientmax = 10;
		// INCORRECT
	}
}
