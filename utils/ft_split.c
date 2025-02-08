/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:30:51 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/08 00:29:09 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	check_sep(char set, char c)
{
	if (set == c)
		return (1);
	return (0);
}

static char	*ft_create_word(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && check_sep(str[i], c) == 0)
		i++;
	word = (char *)malloc(i + 1);
	if (!word)
		return (perror("malloc"), NULL);
	i = 0;
	while (str[i] && check_sep(str[i], c) == 0)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**free_ptr(char **split, int i)
{
	while (--i >= 0)
		free(split[i]);
	free(split);
	return (NULL);
}

static char	**terminate(char **split, int i, char *added_word)
{
	if (added_word != NULL)
		split[0] = added_word;
	split[i] = 0;
	return (split);
}

char	**ft_split(char *s, char c, char *added_word)
{
	char	**split;
	int		i;

	split = (char **)malloc((count_words(s, c) + 1
				+ (added_word != NULL)) * sizeof(char *));
	if (!split)
		return (perror("malloc"), NULL);
	i = added_word != NULL;
	if (!s)
		return (terminate(split, i, added_word));
	while (*s)
	{
		while (*s && check_sep(*s, c))
			s++;
		if (*s && check_sep(*s, c) == 0)
		{
			split[i] = ft_create_word(s, c);
			if (split[i] == NULL)
				return (free_ptr(split, i));
			while (*s && check_sep(*s, c) == 0)
				s++;
			i++;
		}
	}
	return (terminate(split, i, added_word));
}
