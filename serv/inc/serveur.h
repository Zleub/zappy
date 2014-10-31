/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 16:15:34 by adebray           #+#    #+#             */
/*   Updated: 2014/10/31 23:45:07 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

typedef struct	s_env
{
	// GETOPT
	char		*port;
	int			x;
	int			y;
	char		*name;
	int			clientmax;
	// SOCKET()
	int			namespace;
	int			style;
	int			protocol;
}				t_env;

typedef struct	s_client
{

}				t_client;

void	ft_print_env(t_env *env);
void	ft_fill_env(t_env *env, char ch, char *optarg);

#endif
