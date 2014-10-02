/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 19:18:37 by garm              #+#    #+#             */
/*   Updated: 2014/10/02 15:48:30 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsock.h>

int		ftsock_perror(char error)
{
	if (error == FTSOCK_SOCKETERROR)
		ft_putendl_fd(FTSOCK_SOCKETERROR_STR, 2);
	else if (error == FTSOCK_BINDERROR)
		ft_putendl_fd(FTSOCK_BINDERROR_STR, 2);
	else if (error == FTSOCK_LISTENERROR)
		ft_putendl_fd(FTSOCK_LISTENERROR_STR, 2);
	else if (error == FTSOCK_ACCEPTERROR)
		ft_putendl_fd(FTSOCK_ACCEPTERROR_STR, 2);
	else if (error == FTSOCK_CONNECTERROR)
		ft_putendl_fd(FTSOCK_CONNECTERROR_STR, 2);
	else if (error == FTSOCK_MUSTBE_CLIENT)
		ft_putendl_fd(FTSOCK_MUSTBE_CLIENT_STR, 2);
	else if (error == FTSOCK_MUSTBE_SERVER)
		ft_putendl_fd(FTSOCK_MUSTBE_SERVER_STR, 2);
	else if (error == FTSOCK_BAD_PORT)
		ft_putendl_fd(FTSOCK_BAD_PORT_STR, 2);
	else if (error == FTSOCK_SETSOCK_ERROR)
		ft_putendl_fd(FTSOCK_SETSOCK_ERROR_STR, 2);
	return (1);
}
