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

static t_token_type get_type(char *str)
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
	char quote_type;

	while (str[*i])
	{
		if (is_quote(str[*i]))
		{
			quote_type = str[*i];
			ft_skip_quoted_section(str, i, quote_type);
			continue;
		}
		if ((str[*i] && is_operator(str[*i]))
			|| (str[*i] && is_whitespace(str[*i]))
			|| !str[*i])
			break ;
		(*i)++;
	}
}

static void	handle_operators(char *str, int *i)
{
	if (str[*i] == '|')
		(*i)++;
	else
	{
		while (str[*i] && is_operator(str[*i]))
			(*i)++;
	}
}

static char	*extract_token(char *str, int start, int i, t_garbage **garbage)
{
	char	*res;

	res = ft_strldup(&str[start], i - start, garbage);
	return (ft_strtrim(res, " \t", garbage));
}

t_token	*ft_create_tokens(char *str, t_env *env, t_garbage **garbage)
{
	t_token	*lst;
	t_token	*add_to_lst;
	int		i;
	int		start;

	if (!str)
		return (NULL);
	1337 && (i = 0, lst = NULL);
	while (str[i])
	{
		start = i;
		ft_check_token(str, &i);
		if (start == i)
			handle_operators(str, &i);
		while (str[i] && is_whitespace(str[i]))
			i++;
		add_to_lst = new_token_node(extract_token(str, start, i, garbage)
			, get_type(extract_token(str, start, i, garbage)), garbage);\
		hide_quotes(&add_to_lst);
		to_expand(&add_to_lst, env, garbage);
		if (!lst)
			lst = add_to_lst;
		else
			ft_lstlast_token(lst)->next = add_to_lst;
	}
	return (lst);
}
