/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-06 12:27:57 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-06 12:27:57 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	strlen_pars(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	syntax_error(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->type == PIPE)
		return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next || tmp->next->type == PIPE)
				return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
		}
		else if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND || tmp->type == HERE_DOC)
		{
			if (!tmp->next ||tmp->next->type == PIPE
				|| tmp->next->type == REDIR_IN || tmp->next->type == REDIR_OUT
				|| tmp->next->type == REDIR_APPEND || tmp->next->type == HERE_DOC)
				return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
