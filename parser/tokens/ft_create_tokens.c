/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 12:15:24 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-18 12:15:24 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token_type ft_get_token_type(char *str)
{
	if (!str)
		return (WORD);
	if (str[0] == '|')
		return (PIPE);
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		return (REDIR_OUTPUT);
	}
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HERE_DOC);
		return (REDIR_INPUT);
	}
	return (WORD);
}

static void	ft_check_token(char *str, int *i)
{
	while (str[*i])
	{
		if (is_quote(str[*i]))
			ft_skip_quotes(str, i);
		if (str[*i] && is_operator(str[*i])
			|| str[*i] && is_whitespace(str[*i])
			|| !str[*i])
			break ;
		(*i)++;
	}
}