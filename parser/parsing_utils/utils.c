/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 09:23:03 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-17 09:23:03 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_redir(char c)
{
	return (c == '>' || c == '<');
}

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	init_syntax_data(int *i, char *line)
{
	*i = 0;
	if (!line || line[*i] == '|')
		return (ft_putstr_fd("minishell: syntax error\n", 2), -1);
	return (0);
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
