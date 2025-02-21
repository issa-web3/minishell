/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:58:03 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 10:48:41 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s1, t_garbage **my_garbage)
{
	char	*copy;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen((char *)s1);
	copy = (char *)ft_malloc((len + 1) * sizeof(char), my_garbage);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}
