/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:47:57 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/14 10:12:57 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**extract(char **old_str, char *new, t_garbage **garbage)
{
	char	**new_str;
	int		i;

	i = 0;
	if (!old_str)
	{
		new_str = ft_malloc(sizeof(char *) * 2, garbage);
		new_str[0] = ft_strdup(new, garbage);
		new_str[1] = NULL;
	}
	else
	{
		while (old_str[i])
			i++;
		new_str = ft_malloc(sizeof(char *) * (i + 2), garbage);
		i = 0;
		while (old_str[i])
		{
			new_str[i] = ft_strdup(old_str[i], garbage);
			i++;
		}
		new_str[i] = ft_strdup(new, garbage);
		new_str[i + 1] = NULL;
	}
	return (new_str);
}

void	ft_handle_cmd(t_2_exec **node, t_garbage **garbage, t_token **tokens)
{
	char	**cmds;

	cmds = (*node)->cmd;
	while ((*tokens) && (*tokens)->type == WORD)
	{
		cmds = extract(cmds, (*tokens)->token, garbage);
		(*tokens) = (*tokens)->next;
	}
	(*node)->cmd = cmds;
}

int	is_only_whitespace(char *str)
{
	int	i;

	if (!str || !*str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_hquote(char c)
{
	if (c == -1)
		return (1);
	if (c == -2)
		return (2);
	return (0);
}

void	ft_skip_spaces(char	*s, int *i)
{
	while (s[*i] && is_whitespace(s[*i]))
		(*i)++;
}
