/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-06 08:42:50 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-06 08:42:50 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unclosed_quotes(char *line)
{
	int	i;
	int	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (quote != line[i])
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}

int	quoted(char *str, int index)
{
	int	i;
	int	k;
	int	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			k = i++;
			while (str[i] && str[i] != quote)
				i++;
			if (index >= k && index <= i)
				return (quote);
		}
		if (str[i])
			i++;
	}
	return (0);
}

static void	ft_get_len(char *input, int i, int *new_len)
{
	if (input[i] == '>' || input[i] == '<')
	{
		if ((input[i] == '>' && input[i + 1] == '>')
			|| (input[i] == '<' && input[i + 1] == '<'))
		{
			if (i > 0 && !is_whitespace(input[i - 1]))
				(*new_len)++;
			if (input[i + 2] && !is_whitespace(input[i + 2]))
				(*new_len)++;
			i++;
		}
		else
		{
			if (i > 0 && !is_whitespace(input[i - 1]))
				(*new_len)++;
			if (input[i + 1] && !is_whitespace(input[i + 1]))
				(*new_len)++;
		}
	}
}

int	calc_new_len(char *input)
{
	int	i;
	int	new_len;

	i = -1;
	new_len = strlen_pars(input);
	while (input[++i])
	{
		if ((input[i] == '>' || input[i] == '<') && !quoted(input, i))
			ft_get_len(input, i, &new_len);
		else if (input[i] == '|' && !quoted(input, i))
		{
			if (i > 0 && !is_whitespace(input[i - 1]))
				new_len++;
			if (input[i + 1] && !is_whitespace(input[i + 1]))
				new_len++;
		}
	}
	return (new_len);
}
