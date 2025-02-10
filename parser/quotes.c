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
