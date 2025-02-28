/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 10:36:31 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-28 10:36:31 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	toggle_quote(char c, char *quote)
{
	if (*quote == 0)
		*quote = c;
	else
		*quote = 0;
}

static char	*ft_create_word(char *str, t_garbage **my_garbage)
{
	char	*word;
	char	quote_type;
	int		i;
	int		j;

	1 && (i = 0, quote_type = 0);
	while (str[i] && (is_whitespace(str[i]) == 0 || quote_type))
	{
		if ((str[i] == '"' || str[i] == '\'')
			&& (quote_type == 0 || quote_type == str[i]))
			toggle_quote(str[i], &quote_type);
		i++;
	}
	word = (char *)ft_malloc(i + 1, my_garbage);
	1 && (i = 0, j = 0, quote_type = 0);
	while (str[i] && (is_whitespace(str[i]) == 0 || quote_type))
	{
		word[j++] = str[i];
		if ((str[i] == '"' || str[i] == '\'')
			&& (quote_type == 0 || quote_type == str[i]))
			toggle_quote(str[i], &quote_type);
		i++;
	}
	return (word[j] = 0, word);
}

char	**ft_strtok(char *s, t_garbage **my_garbage)
{
	char	**split;
	int		i;
	char	quote_type;

	if (!s)
		return (NULL);
	1 && (split = (char **)ft_malloc((count_words(s, ' ') + 1)
			* sizeof(char *), my_garbage), i = 0);
	while (*s)
	{
		while (*s && is_whitespace(*s))
			s++;
		if (*s && is_whitespace(*s) == 0)
		{
			split[i++] = ft_create_word(s, my_garbage);
			quote_type = 0;
			while (*s && (is_whitespace(*s) == 0 || quote_type))
			{
				if (is_quote(*s) && (quote_type == 0 || quote_type == *s))
					toggle_quote(*s, &quote_type);
				s++;
			}
		}
	}
	return (split[i] = 0, split);
}
