/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 16:15:34 by adebray           #+#    #+#             */
/*   Updated: 2014/11/01 15:53:18 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

#include <stdio.h>
#include <libft.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

enum
{
							NEW,
							GET,
							ADD,
							PRINT
};

typedef struct				s_env
{
	// GETOPT
	int						port;
	int						x;
	int						y;
	char					*name;
	int						clientmax;
	// SOCKETS
	int						ipv4_socket;
	struct sockaddr_in		sin;

}							t_env;

typedef struct				s_client
{
	struct sockaddr_in		sin;
}							t_client;

typedef struct				s_client_list
{
	t_client				*elem;
	struct s_client_list	*next;
}							t_client_list;

void						ft_print_env(t_env *env);
void						ft_fill_env(t_env *env, char ch, char *optarg);
t_client					*manage_client(int macro);
t_client_list				*manage_client_list(int macro, t_client *client);

#endif
