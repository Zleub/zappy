/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 16:15:34 by adebray           #+#    #+#             */
/*   Updated: 2014/11/03 04:51:07 by adebray          ###   ########.fr       */
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
							INIT,
							FILL
};

enum
{
							LOBBY
};

typedef struct				s_client
{
	int						fd;
	int						state;
	struct sockaddr_in		sin;
}							t_client;

typedef struct				s_client_list
{
	t_client				*elem;
	struct s_client_list	*next;
}							t_client_list;

typedef struct				s_team_list
{
	char					*elem;
	int						slots;
	t_client_list			*players;
	struct s_team_list		*next;
}							t_team_list;

typedef struct				s_env
{
	// SELF
	char					this_char;
	char					*this_str;
	// GETOPT
	int						port;
	int						x;
	int						y;
	int						clientmax;
	t_team_list				*teams;
	// SOCKETS
	int						ipv4_socket;
	struct sockaddr_in		sin;
	fd_set					active_fd_set;
}							t_env;

t_env						*ft_manage_env(int macro);
t_client					*manage_client(int macro);
t_client_list				*manage_client_list(int macro, t_client *client, int fd);
void						print_client(t_client *client);
int							ft_sockloop(t_env *env);


t_team_list				*new_team_list(char *str);
t_team_list				*add_team_list(t_team_list *head, t_team_list *elem);
t_team_list				*manage_team_list(int macro, t_team_list *elem);

#endif
