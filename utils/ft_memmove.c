/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 08:41:55 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/05 13:09:38 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d_str_pos;
	char	*s_str_pos;

	if (dst == src)
		return (dst);
	d_str_pos = (char *)dst;
	s_str_pos = (char *)src;
	if (s_str_pos < d_str_pos)
	{
		while (len-- > 0)
			d_str_pos[len] = s_str_pos[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			d_str_pos[i] = s_str_pos[i];
			i++;
		}
	}
	return (dst);
}
