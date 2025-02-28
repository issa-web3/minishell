/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:30:51 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 13:40:18 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_sep(char set, char c)
{
	if (set == c)
		return (1);
	return (0);
}

static char	*ft_create_word(const char *str, char c, t_garbage **my_garbage)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && is_sep(str[i], c) == 0)
		i++;
	word = (char *)ft_malloc(i + 1, my_garbage);
	i = 0;
	while (str[i] && is_sep(str[i], c) == 0)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char *s, char c, t_garbage **my_garbage)
{
	char	**split;
	int		i;

	if (!s)
		return (NULL);
	split = (char **)ft_malloc((count_words(s, c) + 1)
			* sizeof(char *), my_garbage);
	i = 0;
	while (*s)
	{
		while (*s && is_sep(*s, c))
			s++;
		if (*s && is_sep(*s, c) == 0)
		{
			split[i] = ft_create_word(s, c, my_garbage);
			while (*s && is_sep(*s, c) == 0)
				s++;
			i++;
		}
	}
	split[i] = 0;
	return (split);
}
