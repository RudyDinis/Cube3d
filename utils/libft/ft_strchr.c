/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:21:28 by rdinis            #+#    #+#             */
/*   Updated: 2025/11/11 13:46:51 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( const char	*string, int searchedChar )
{
	while (*string)
	{
		if (*string == (char)searchedChar)
			return ((char *)string);
		string++;
	}
	if ((char)searchedChar == '\0')
		return ((char *)string);
	return (NULL);
}
