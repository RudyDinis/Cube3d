/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:36:18 by rdinis            #+#    #+#             */
/*   Updated: 2025/11/11 13:48:01 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr( const char *string, int searchedChar )
{
	int	indice;

	indice = 0;
	while (string[indice])
		indice++;
	while (indice >= 0)
	{
		if (string[indice] == (char)searchedChar)
			return ((char *)&string[indice]);
		indice--;
	}
	return (NULL);
}
