/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:29:55 by rdinis            #+#    #+#             */
/*   Updated: 2025/11/11 13:46:57 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	i = 0;
	if (!str)
		return (NULL);
	j = 0;
	while (j < ft_strlen(s1))
		str[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
		str[i++] = s2[j++];
	return (str);
}
