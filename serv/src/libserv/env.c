/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/31 11:22:13 by Arno              #+#    #+#             */
/*   Updated: 2014/11/03 04:15:54 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

static void				ft_print_env(t_env *env)
{
	printf("port->%d\n", env->port);
	printf("x->%d\n", env->x);
	printf("y->%d\n", env->y);
	printf("teams->%p\n", env->teams);
	manage_team_list(PRINT, NULL);
	printf("clientmax->%d\n", env->clientmax);
}

static void				ft_fill_env(t_env *env)
{
	if (env->this_char == 'p')
		env->port = ft_atoi(env->this_str);
	else if (env->this_char == 'x')
		env->x = ft_atoi(env->this_str);
	else if (env->this_char == 'y')
		env->y = ft_atoi(env->this_str);
	else if (env->this_char == 'n')
	{
		while (env->this_str[0] != '-' && strncmp(env->this_str, "PATH", 4))
		{
			new_team_list(env->this_str);
			env->this_str += strlen(env->this_str) + 1;
		}
		env->teams = manage_team_list(GET, NULL);
	}
	else if (env->this_char == 'c')
		env->clientmax = ft_atoi(env->this_str);
}

static t_env			*ft_init_env(void)
{
	t_env			*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	bzero(env, sizeof(t_env));
	env->x = 10;
	env->y = 10;
	env->clientmax = 10;
	return (env);
}

t_env					*ft_manage_env(int macro)
{
	static t_env	*env;

	if (macro == INIT)
		env = ft_init_env();
	else if (macro == FILL)
		ft_fill_env(env);
	else if (macro == PRINT)
		ft_print_env(env);
	else if (macro == GET)
		return (env);
	else
		printf("manageenv: no decent macro: %d\n", macro);
	return (NULL);
}
