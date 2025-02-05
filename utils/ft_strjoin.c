/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:11:41 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/05 13:09:38 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	size1;
	size_t	size2;
	size_t	allocated;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	allocated = sizeof(char) * ((size1 + size2) + 1);
	result = malloc(allocated);
	if (!result)
		return (result);
	ft_strlcpy(result, s1, size1 + 1);
	ft_strlcat(result, s2, allocated);
	return (result);
}
