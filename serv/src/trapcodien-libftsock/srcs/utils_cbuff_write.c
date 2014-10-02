/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cbuff_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/29 22:33:39 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:20:12 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsock.h"

int			utils_cbuff_write(t_cbuff *b, void *data, size_t len)
{
	size_t		i;
	char		*mem;

	if (!b || !data)
		return (ERROR);
	if (len == 0)
		return (0);
	mem = (char *)data;
	i = 0;
	while (i < len)
	{
		if (b->offset >= (long)b->size - 1)
			b->offset = 0;
		*((char *)b->data + b->offset) = mem[i];
		b->offset++;
		i++;
	}
	return (len);
}

