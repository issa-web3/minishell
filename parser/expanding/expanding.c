/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-25 03:27:22 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-25 03:27:22 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_between_quotes(char *str, int *i, int quote, t_garbage **garbage)
{
	char	*res;
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && is_quote(str[*i]) != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
	res = ft_strldup(&str[start], *i - start, garbage);
	return (res);
}

static void	create_plain_seg(char *str, char **res, int *i, t_garbage **garbage)
{
	int	start;

	start = *i;
	while (str[*i] && !is_quote(str[*i]))
		(*i)++;
	if (start != *i)
		*res = ft_strldup(&str[start], *i - start, garbage);
}

static t_expand	*create_expand_lst(char *str, t_garbage **garbage)
{
	t_expand	*lst;
	t_expand	*node;
	char		*segment;
	int			i;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		node = 	ft_create_expand_node(NULL, garbage);
		segment = NULL;
		node->is_expand = 1;
		if (str[i] && is_quote(str[i]) == 1)
		{
			segment = get_between_quotes(str, &i, 1, garbage);
			node->is_expand = 0;
		}
		else if (str[i] && is_quote(str[i]) == 2)
			segment = get_between_quotes(str, &i, 2, garbage);
		else
			create_plain_seg(str, &segment, &i, garbage);
		node->value = segment;
		ft_lstadd_back_t_expand(&lst, node);
	}
	return (lst);
}

char	*expand_dollar_variable(char *str, t_env *env, t_garbage **garbage)
{
	t_expand	*lst;
	t_expand	*curr;
	char		*res;

	lst = create_expand_lst(str, garbage);
	curr = lst;
	res = NULL;
	while (curr)
	{
		if (curr->is_expand)
			curr->value = ft_replace_dollar(curr->value, env, garbage);
		curr = curr->next;
	}
	curr = lst;
	while (curr)
	{
		res = ft_strjoin(res, curr->value, garbage);
		curr = curr->next;
	}
	return (res);
}

void	ft_expand_token(t_token **node, t_env *envl, t_garbage **garbage)
{
	int		i;
	t_token	*new;
	char 	**toks;
	int		is_export;
	int		n;

	i = 0;
	check_export(node, &is_export);
	if ((*node) && (*node)->type == WORD)
	{
		(*node)->token = expand_dollar_variable((*node)->token, envl, garbage);
		(*node)->expanded = 1;
		n = my_count_words((*node)->token);
		if (n > 1 && !is_export)
		{
			toks = ft_strtok((*node)->token, garbage);
			(*node)->token = ft_strdup(toks[i++], garbage);
			(*node)->type = WORD;
			while (i < n)
			{
				new = new_token_node(toks[i++], WORD, 1, garbage);
				ft_append_to_lst(node, new);
			}
		}
	}
}
