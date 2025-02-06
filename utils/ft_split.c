/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:30:51 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/06 14:28:36 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	check_sep(char set, char c)
{
	if (set == c)
		return (1);
	return (0);
}

static int	count_words(const char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && check_sep(str[i], c) == 1)
			i++;
		if (str[i] && check_sep(str[i], c) == 0)
		{
			count++;
			while (str[i] && check_sep(str[i], c) == 0)
				i++;
		}
	}
	return (count);
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

static char	**free_ptr(char **split, int i)
{
	while (--i >= 0)
		free(split[i]);
	free(split);
	return (NULL);
}

static void	append_word(char **split, int i, char *added_word)
{
	split[i] = added_word;
	if (added_word != NULL)
		split[i + 1] = 0;
}

char	**ft_split(char const *s, char c, char *added_word)
{
	char	**split;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	split = (char **)malloc((count_words(s, c) + 1 + (added_word != NULL)) * sizeof(char *));
	if (!split)
		return (perror("malloc"), NULL);
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
	append_word(split, i, added_word);
	return (split);
}
