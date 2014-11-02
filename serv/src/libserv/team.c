/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/02 19:25:31 by Arno              #+#    #+#             */
/*   Updated: 2014/11/02 19:47:53 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

t_team_list				*new_team_list(char *str)
{
	t_team_list			*new;

	if (!(new = (t_team_list*)malloc(sizeof(t_team_list))))
		exit (0);
	new->elem = strdup(str);
	manage_team_list(ADD, new);
	return (new);
}

t_team_list				*add_team_list(t_team_list *head, t_team_list *elem)
{
	t_team_list			*tmp;

	if (!head)
		return (elem);
	else
	{
		tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = elem;
		return (head);
	}
}

void					print_team_list(t_team_list *head)
{
	if (head)
	{
		printf("team %p -> %s\n", head, head->elem);
		print_team_list(head->next);
	}
}

t_team_list				*manage_team_list(int macro, t_team_list *elem)
{
	static t_team_list	*head;

	if (macro == ADD)
		head = add_team_list(head, elem);
	else if (macro == GET)
		return (head);
	else if (macro == PRINT)
		print_team_list(head);
	else
		printf("manageteamlist: no decent macro: %d\n", macro);
	return (NULL);
}
