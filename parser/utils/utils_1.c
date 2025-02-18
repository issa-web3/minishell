/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 15:14:18 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-17 15:14:18 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr(char *s, int start, size_t len, t_garbage **to_free)
{
	char	*sub_str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub_str = ft_malloc(len + 1, to_free);
	if (!sub_str)
		return (NULL);
	while (i < len)
	{
		sub_str[i] = s[i + start];
		i++;
	}
	sub_str[i] = 0;
	return (sub_str);
}

char	*ft_strtrim(char *str, char *set, t_garbage **to_free)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!str || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	while (end > start && ft_strchr(set, str[end - 1]))
		end--;
	res = ft_substr(str, (int)start, end - start, to_free);
	return (res);
}
