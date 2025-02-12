/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:16:27 by khoukouj          #+#    #+#             */
/*   Updated: 2024/07/16 08:57:18 by khoukouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pars_word(char *line, int *i)
{
	char quote;
	while (line[*i] && !is_whitespace(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
}

int	ft_count_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (line[i])
		{
			count++;
			pars_word(line, &i);
		}
		i++;
	}
	return (count);
}

static int	token_len(char *line)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (line[i] && !is_whitespace(line[i]))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			count++;
			while (line[i] && line[i] != quote)
				count += (++i, 1);
			if (line[i])
				count += (++i, 1);
		}
		else
			(count++, i++);
	}
	return (count);
}

static char	*extract_token(char **line)
{
	int		i;
	char	*token;
	int		token_size;

	while (**line && is_whitespace(**line))
		(*line)++;
	token_size = token_len(*line);
	if (token_size == 0)
		return (NULL);
	token = malloc(token_size + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (i < token_size)
	{
		token[i++] = **line;
		(*line)++;
	}
	token[i] = '\0';
	return (token);
}

char	**str_tokenize(char *line)
{
	int		n_of_tokens;
	char	**tokens;
	int		i;

	if (!line)
		return (NULL);
	n_of_tokens = ft_count_tokens(line);
	if (n_of_tokens == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (n_of_tokens + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < n_of_tokens)
	{
		tokens[i] = extract_token(&line);
		if (!tokens[i])
		{
			while (i > 0)
				free(tokens[--i]);
			free(tokens);
			return (NULL);
		}
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
