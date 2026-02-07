/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:38:40 by rdinis            #+#    #+#             */
/*   Updated: 2025/11/11 14:28:04 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr( const void *memoryBlock, int searchedChar, size_t size )
{
	size_t			i;
	unsigned char	*memory;

	memory = (unsigned char *)memoryBlock;
	i = 0;
	while (i < size)
	{
		if (memory[i] == (unsigned char)searchedChar)
			return ((void *)&memory[i]);
		i++;
	}
	return (NULL);
}
