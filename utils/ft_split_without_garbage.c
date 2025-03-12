/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_without_garbage.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:30:51 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/12 01:12:50 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*ft_create_word_wg(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && is_sep(str[i], c) == 0)
		i++;
	word = (char *)malloc(i + 1);
	if (word == NULL)
		return (perror("malloc"), NULL);
	i = 0;
	while (str[i] && is_sep(str[i], c) == 0)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

void	free_split(char **split, int i)
{
	while (--i >= 0)
		free(split[i]);
	free(split);
}

char	**ft_split_without_garbage(char *s, char c)
{
	char	**split;
	int		i;

	if (!s)
		return (NULL);
	split = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (perror("malloc"), NULL);
	i = 0;
	while (*s)
	{
		while (*s && is_sep(*s, c))
			s++;
		if (*s && is_sep(*s, c) == 0)
		{
			split[i] = ft_create_word_wg(s, c);
			if (split[i] == NULL)
				return (perror("malloc"), free_split(split, i), NULL); // TODO free_split
			while (*s && is_sep(*s, c) == 0)
				s++;
			i++;
		}
	}
	split[i] = 0;
	return (split);
}
