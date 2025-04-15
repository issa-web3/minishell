/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_wg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:58:03 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/15 07:24:53 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup_wg(const char *s1, t_garbage **my_garbage)
{
	char	*copy;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen((char *)s1);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (perror("malloc"), clear_all(my_garbage), NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}
