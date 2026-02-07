/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:53:12 by rdinis            #+#    #+#             */
/*   Updated: 2025/11/11 13:18:43 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			indice;
	unsigned char	*p;

	p = (unsigned char *)s;
	indice = 0;
	while (indice < n)
	{
		p[indice] = (unsigned char)c;
		indice++;
	}
	return (s);
}
