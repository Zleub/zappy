/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_win_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/15 14:55:33 by adebray           #+#    #+#             */
/*   Updated: 2014/07/27 17:44:21 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curse.h>

t_win_list	*create_win_list(void)
{
	t_win_list	*new;

	if(!(new = (t_win_list*)malloc(sizeof(t_win_list))))
		return (NULL);
	new->win = NULL;
	new->next = NULL;
	return (new);
}

t_win_list		*add_win_list(t_win_list *head, WINDOW *object)
{
	t_win_list	*tmp;

	if (!head)
	{
		head = create_win_list();
		head->win = object;
	}
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_win_list();
		tmp->next->win = object;
	}
	return (head);
}

void		print_win_list(t_win_list *head)
{
	int		fd;
	t_win_list	*tmp;

	if (!(fd = open("print_win_list", O_CREAT | O_TRUNC | O_WRONLY, 0755)))
		return ;
	tmp = head;
	while (tmp)
	{
		print_win_fd(tmp->win, fd);
		tmp = tmp->next;
	}
	close(fd);
}

t_win_list		*destroy_win_list(t_win_list *head)
{
	if (head)
	{
		destroy_win(head->win);
		head->win = NULL;
		destroy_win_list(head->next);
		free(head);
		head = NULL;
	}
	return (NULL);
}

t_win_list		*manage_win_list(int macro, WINDOW *object)
{
	static t_win_list	*head;

	if (macro == GET)
		return (head);
	// else if (macro == SET)
	// 	head = object;
	else if (macro == ADD)
		head = add_win_list(head, object);
	else if (macro == PRINT)
		print_win_list(head);
	else if (macro == DELETE)
		head = destroy_win_list(head);
	else
		ft_printf("%d: Useless call to manage_win_list\n", macro);
	return (NULL);
}
