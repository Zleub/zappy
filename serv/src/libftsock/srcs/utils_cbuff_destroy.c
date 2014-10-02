/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cbuff_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/29 22:30:58 by garm              #+#    #+#             */
/*   Updated: 2014/10/02 15:49:44 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsock.h>

void		utils_cbuff_destroy(t_cbuff **b)
{
	if (b && *b)
	{
		if ((*b)->data)
			ft_memdel((void **)&(*b)->data);
		ft_memdel((void **)b);
	}
}
