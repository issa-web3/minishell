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
	if (!res)
		return (NULL);
	return (ft_strtrim(res, " \t", garbage));
}

t_token	*ft_create_tokens(char *str, t_env *env, t_garbage **garbage)
{
	t_token	*lst;
	t_token	*add_to_lst;
	int		i;
	int		start;

	i = 0;
	lst = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		add_to_lst = ft_malloc(sizeof(t_token), garbage);
		start = i;
		ft_check_token(str, &i);
		if (start == i)
			handle_operators(str, &i);
		while (str[i] && is_whitespace(str[i]))
			i++;
		add_to_lst->token = extract_token(str, start, i, garbage);
		add_to_lst->type = ft_get_token_type(add_to_lst->token);
		add_to_lst->expanded = 0;
		 if (can_i_expand(add_to_lst->token))
			ft_expand_token(&add_to_lst, env, garbage);
		ft_append_to_lst(&lst, add_to_lst);
	}
	return (lst);
}
