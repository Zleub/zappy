/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/01 15:26:28 by adebray           #+#    #+#             */
/*   Updated: 2014/11/02 17:24:02 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

static t_client			*new_client(void)
{
	t_client			*new;

	// printf("new client\n");
	if (!(new = (t_client*)malloc(sizeof(t_client))))
		exit (0);
	manage_client_list(ADD, new, 0);
	return (new);
}

void					print_client(t_client *client)
{
	printf("\tprint_client\n");
	printf("\tfd: %d -> %p\n", client->fd, &client->sin);
}

t_client				*manage_client(int macro)
{
	static t_client		*current;

	if (macro == NEW)
		current = new_client();
	else if (macro == GET)
		return (current);
	else
		printf("manageclient: no decent macro");
	return (NULL);
}
