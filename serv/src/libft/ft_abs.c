/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/05 20:50:32 by adebray           #+#    #+#             */
/*   Updated: 2014/08/05 20:50:38 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_abs(int x)
{
	if (x >= 0)
		return (x);
	else
		return (x * -1);
}
