/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/31 11:22:13 by Arno              #+#    #+#             */
/*   Updated: 2014/10/31 12:26:52 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <serveur.h>
#include <libft.h>

void	ft_print_env(t_env *env)
{
	ft_printf("port->%s\n", env->port);
	ft_printf("x->%d\n", env->x);
	ft_printf("y->%d\n", env->y);
	ft_printf("name->%s\n", env->name);
	ft_printf("clientmax->%d\n", env->clientmax);
}

void	ft_fill_env(t_env *env, char ch, char *optarg)
{
	if (ch == 'p')
		env->port = ft_strdup(optarg);
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
