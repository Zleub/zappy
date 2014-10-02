/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsock_resolve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garm <garm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 19:17:08 by garm              #+#    #+#             */
/*   Updated: 2014/09/28 22:20:22 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsock.h"

void		ftsock_resolve_host(t_tcpsock *host, char *dns)
{
	struct hostent		*he;

	if ((he = gethostbyname(dns)))
		ft_memcpy(&(host->sin.sin_addr), he->h_addr_list[0], he->h_length);
	else
		host->sin.sin_addr.s_addr = inet_addr(dns);
}
