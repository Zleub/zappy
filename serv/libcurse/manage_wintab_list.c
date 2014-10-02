/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wintab_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/16 02:44:53 by adebray           #+#    #+#             */
/*   Updated: 2014/07/19 02:33:45 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curse.h>

WINTABLIST		*create_wintab_list(void)
{
	WINTABLIST	*new;

	if(!(new = (WINTABLIST*)malloc(sizeof(WINTABLIST))))
		return (NULL);
	new->array = NULL;
	new->next = NULL;
	return (new);
}

WINTABLIST		*add_wintab_list(WINTABLIST *head, WINTAB *object)
{
	WINTABLIST	*tmp;

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

void		print_wintab_list(WINTABLIST *head)
{
	int		fd;
	WINTABLIST	*tmp;

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

WINTABLIST		*destroy_wintab_list(WINTABLIST *head)
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

WINTABLIST		*manage_wintab_list(int macro, WINTAB *array)
{
	static WINTABLIST	*head;

	if (macro == GET)
		return (head);
	// else if (macro == SET)
	// {
	// 	if (head && !head->array)
	// 		head->array = array;
	// 	else
	// 		ft_printf("Head already set\n");
	// }
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
