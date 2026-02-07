/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:27:08 by rdinis            #+#    #+#             */
/*   Updated: 2025/11/11 11:36:59 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc( size_t elementCount, size_t elementSize )
{
	unsigned char	*pointer;
	size_t			i;

	if (elementCount != 0 && elementSize > SIZE_MAX / elementCount)
		return (NULL);
	pointer = malloc(elementCount * elementSize);
	if (!pointer)
		return (NULL);
	i = 0;
	while (i < elementCount * elementSize)
	{
		pointer[i] = 0;
		i++;
	}
	return (pointer);
}
