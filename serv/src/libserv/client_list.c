/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/01 15:36:49 by adebray           #+#    #+#             */
/*   Updated: 2014/11/02 17:10:11 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

static t_client_list		*new_client_list(t_client *client)
{
	t_client_list			*new;

	if (!(new = (t_client_list*)malloc(sizeof(t_client_list))))
		exit (0);
	new->elem = client;
	new->next = NULL;
	return (new);
}

static t_client_list		*add_client_list(t_client_list *head, t_client *client)
{
	t_client_list			*tmp;

	if (head == NULL)
		head = new_client_list(client);
	else
	{
		tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_client_list(client);
	}
	return (head);
}

void						print_client_list(t_client_list *head)
{
	printf("client head: %p\n", head);
	if (head)
	{
		print_client(head->elem);
		if (head->next != NULL)
			print_client_list(head->next);
	}
}

t_client_list				*remove_client_list(t_client_list *head, int fd)
{
	t_client_list			*tmp;
	t_client_list			*t;

	tmp = head;
	if (tmp->elem->fd == fd)
	{
		t = tmp->next;
		free(tmp);
		return (t);
	}
	while (tmp->next->elem->fd != fd)
		tmp = tmp->next;
	free(tmp->next);
	tmp->next = tmp->next->next;
	return (head);
}

t_client_list				*manage_client_list(int macro, t_client *client, int fd)
{
	static t_client_list	*head;

	if (macro == ADD)
		head = add_client_list(head, client);
	else if (macro == GET)
		return (head);
	else if (macro == REMOVE)
		head = remove_client_list(head, fd);
	else if (macro == PRINT)
		print_client_list(head);
	else
		printf("manageclientlist: no decent macro: %d\n", macro);
	return (NULL);
}
