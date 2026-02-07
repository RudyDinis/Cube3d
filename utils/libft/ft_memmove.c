/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:48:52 by rdinis            #+#    #+#             */
/*   Updated: 2025/11/11 15:47:55 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	c_dst = (unsigned char *)dst;
	c_src = (const unsigned char *)src;
	if (c_dst > c_src)
	{
		while (len--)
			c_dst[len] = c_src[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			c_dst[i] = c_src[i];
			i++;
		}
	}
	return (dst);
}
