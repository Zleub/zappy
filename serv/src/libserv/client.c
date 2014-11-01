/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/01 15:26:28 by adebray           #+#    #+#             */
/*   Updated: 2014/11/01 15:50:23 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

static t_client			*new_client(void)
{
	t_client			*new;

	if (!(new = (t_client*)malloc(sizeof(t_client))))
		exit (0);
	manage_client_list(ADD, new);
	return (new);
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
