/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:23:58 by rdinis            #+#    #+#             */
/*   Updated: 2025/11/11 13:46:53 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*dest;
	size_t	i;

	dest = (char *)malloc(ft_strlen(string) + 1);
	i = 0;
	if (!dest)
		return (NULL);
	while (string[i])
	{
		dest[i] = string[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
