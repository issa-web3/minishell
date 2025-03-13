/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-02 11:51:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025-03-02 11:51:19 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_quoted(char *str, int *index, int q_type, t_garbage **g)
{
	t_extract_info	info;
	char			*res;

	(*index)++;
	info.start = *index;
	info.length = 0;
	while (str[*index] && (is_hquote(str[*index]) != q_type))
	{
		(*index)++;
		info.length++;
	}
	if (str[*index])
		(*index)++;
	res = ft_strldup(&str[info.start], info.length, g);
	return (res);
}

static void	append_char(char *str, char *res, t_indices *indices)
{
	res[indices->result_index] = str[indices->str_index];
	indices->result_index++;
	indices->str_index++;
}

static void	cat_quoted(char *res, char *str, t_indices *indices, t_garbage **g)
{
	char	*inside_quotes;
	int		i;

	inside_quotes = extract_quoted(str, &indices->str_index \
		, is_hquote(str[indices->str_index]), g);
	i = 0;
	while (inside_quotes[i])
		res[(indices->result_index)++] = inside_quotes[i++];
}

char	*remove_quotes(char *str, t_garbage **g)
{
	char		*res;
	t_indices	indices;

	if (!str)
		return (NULL);
	indices.str_index = 0;
	indices.result_index = 0;
	res = ft_malloc(ft_strlen(str) + 1, g);
	while (str[indices.str_index])
	{
		if (str[indices.str_index] == '$')
		{
			if (is_quote(str[indices.str_index + 1]))
				indices.str_index++;
		}
		if (str[indices.str_index] && is_hquote(str[indices.str_index]))
			cat_quoted(res, str, &indices, g);
		else
			append_char(str, res, &indices);
	}
	res[indices.result_index] = '\0';
	return (res);
}

t_token	*remove_quotes_from_toks(t_token *toks, t_garbage **g)
{
	t_token	*curr;

	curr = toks;
	while (curr)
	{
		if (curr->type == HERE_DOC)
			curr = curr->next;
		else if (curr->type == WORD)
			curr->token = remove_quotes(curr->token, g);
		curr = curr->next;
	}
	return(toks);
}
