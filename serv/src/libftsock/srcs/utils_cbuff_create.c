/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cbuff_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/29 22:26:57 by garm              #+#    #+#             */
/*   Updated: 2014/10/02 15:49:38 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsock.h>

t_cbuff		*utils_cbuff_create(size_t size)
{
	t_cbuff		*new;

	if (!size)
		return (NULL);
	new = ft_memalloc(sizeof(t_cbuff));
	if (!new)
		return (NULL);
	new->data = ft_memalloc(size);
	if (!new->data)
	{
		ft_memdel((void **)&new);
		return (NULL);
	}
	new->size = size;
	new->offset = 0;
	return (new);
}
