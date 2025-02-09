/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:11:41 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 11:03:30 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char *s1, char *s2, t_garbage **my_garbage)
{
	char	*result;
	size_t	size1;
	size_t	size2;
	size_t	allocated;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, my_garbage));
	if (!s2)
		return (ft_strdup(s1, my_garbage));
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	allocated = sizeof(char) * ((size1 + size2) + 1);
	result = ft_malloc(allocated, my_garbage);
	if (!result)
		return (result);
	ft_strlcpy(result, s1, size1 + 1);
	ft_strlcat(result, s2, allocated);
	return (result);
}
