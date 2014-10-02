/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wintab_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/16 02:44:53 by adebray           #+#    #+#             */
/*   Updated: 2014/10/02 15:37:59 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curse.h>

t_wintab_list		*create_wintab_list(void)
{
	t_wintab_list	*new;

	if (!(new = (t_wintab_list*)malloc(sizeof(t_wintab_list))))
		return (NULL);
	new->array = NULL;
	new->next = NULL;
	return (new);
}

t_wintab_list		*add_wintab_list(t_wintab_list *head, WINTAB *object)
{
	t_wintab_list	*tmp;

	if (!head)
	{
		head = create_wintab_list();
		head->array = object;
	}
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_wintab_list();
		tmp->next->array = object;
	}
	return (head);
}

void				print_wintab_list(t_wintab_list *head)
{
	int				fd;
	t_wintab_list	*tmp;

	if (!(fd = open("print_wintab_list", O_CREAT | O_TRUNC | O_WRONLY, 0755)))
		return ;
	tmp = head;
	while (tmp)
	{
		print_wintab_fd(tmp->array, fd);
		tmp = tmp->next;
	}
	close(fd);
}

t_wintab_list		*destroy_wintab_list(t_wintab_list *head)
{
	if (head)
	{
		destroy_wintab(head->array);
		if (head->next)
			destroy_wintab_list(head->next);
		free(head);
		head = NULL;
		return (NULL);
	}
	return (NULL);
}

t_wintab_list		*manage_wintab_list(int macro, WINTAB *array)
{
	static t_wintab_list	*head;

	if (macro == GET)
		return (head);
	else if (macro == ADD)
		head = add_wintab_list(head, array);
	else if (macro == PRINT)
		print_wintab_list(head);
	else if (macro == DELETE)
		head = destroy_wintab_list(head);
	else
		ft_printf("Useless call to manage_wintab_list\n");
	return (NULL);
}
