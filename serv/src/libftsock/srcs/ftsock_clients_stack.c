/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_clients_stack.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/28 20:54:59 by garm              #+#    #+#             */
/*   Updated: 2014/10/02 15:48:18 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsock.h>

static t_client		*ftsock_client_new(t_tcpsock *tcps)
{
	t_client	*new;

	new = ft_memalloc(sizeof(t_client));
	if (!new)
		return (NULL);
	new->tcps = tcps;
	new->next = NULL;
	new->user_data = NULL;
	ft_bzero(new->recv_buf, FTSOCK_BUFFER);
	new->recv_cbuf = utils_cbuff_create(FTSOCK_MAXBUF);
	ft_bzero(new->send_buf, FTSOCK_BUFFER);
	new->send_data = NULL;
	new->send_offset = 0;
	new->closed = 0;
	return (new);
}

static void			ftsock_client_destroy(t_client **todel)
{
	if (todel && *todel)
	{
		ftsock_destroy(&(*todel)->tcps);
		(*todel)->next = NULL;
		ft_strdel(&(*todel)->send_data);
		utils_cbuff_destroy(&(*todel)->recv_cbuf);
		ft_memdel((void **)todel);
	}
}
static t_client		*find_before(t_client *stack, t_client *elem)
{
	t_client	*cursor;
	t_client	*before;

	cursor = stack;
	while (cursor)
	{
		before = cursor;
		cursor = cursor->next;
		if (cursor == elem)
			return (before);
	}
	return (NULL);
}


t_client			*ftsock_client_add(t_client *stack, t_tcpsock *tcps)
{
	t_client		*new;

	if (!tcps)
		return (stack);
	new = ftsock_client_new(tcps);
	new->next = stack;
	return (new);
}

void				ftsock_client_del(t_client **stack, t_client **todel)
{
	t_client	*before;
	t_client	*after;

	if (!stack || !*stack || !todel || !*todel)
		return ;
	if (*stack == *todel)
		*stack = (*stack)->next;
	else
	{
		before = find_before(*stack, *todel);
		after = (*todel)->next;
		before->next = after;
	}
	ftsock_client_destroy(todel);
}
