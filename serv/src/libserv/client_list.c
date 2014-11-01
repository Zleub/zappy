/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/01 15:36:49 by adebray           #+#    #+#             */
/*   Updated: 2014/11/01 15:56:52 by adebray          ###   ########.fr       */
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
	printf("%p\nhead->elem:%p, head->next%p\n", head, head->elem, head->next);
	if (head->next != NULL)
		print_client_list(head->next);
}

t_client_list				*manage_client_list(int macro, t_client *client)
{
	static t_client_list	*head;

	if (macro == ADD)
		head = add_client_list(head, client);
	else if (macro == PRINT)
		print_client_list(head);
	else
		printf("manageclientlist: no decent macro");
	return (NULL);
}
