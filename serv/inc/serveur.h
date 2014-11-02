/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 16:15:34 by adebray           #+#    #+#             */
/*   Updated: 2014/11/02 19:42:42 by Arno             ###   ########.fr       */
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

#include <sys/time.h>

#define MAXMSG  1024

enum
{
							NEW,
							GET,
							ADD,
							PRINT,
							REMOVE,
};

typedef struct				s_client
{
	int						fd;
	struct sockaddr_in		sin;
}							t_client;

typedef struct				s_client_list
{
	t_client				*elem;
	struct s_client_list	*next;
}							t_client_list;

typedef struct				s_char_list
{
	char					*elem;
	struct s_char_list		*next;
}							t_char_list;

typedef t_char_list			t_team_list;

typedef struct				s_env
{
	// GETOPT
	int						port;
	int						x;
	int						y;
	t_team_list				*teams;
	int						clientmax;
	// SOCKETS
	int						ipv4_socket;
	struct sockaddr_in		sin;
	fd_set					active_fd_set;
}							t_env;

void						ft_print_env(t_env *env);
void						ft_fill_env(t_env *env, char ch, char *optarg);
t_client					*manage_client(int macro);
t_client_list				*manage_client_list(int macro, t_client *client, int fd);
void						print_client(t_client *client);
int							ft_sockloop(t_env *env);


t_team_list				*new_team_list(char *str);
t_team_list				*add_team_list(t_team_list *head, t_team_list *elem);
t_team_list				*manage_team_list(int macro, t_team_list *elem);

#endif
