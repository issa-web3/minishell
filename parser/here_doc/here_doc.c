/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:04:01 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/21 17:13:10 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	prepare_del(char **del)
{
	char	*tmp;
	int		i;

	tmp = *del;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == -1)
			tmp[i] = '\'';
		else if (tmp[i] == -2)
			tmp[i] = '"';
		i++;
	}
}

int	ft_handle_heredoc(t_token **tokens, t_2_exec **node, t_garbage **g)
{
	char	*del;
	int		is_expand;

	while ((*tokens) && (*tokens)->type == HERE_DOC)
	{
		if ((*tokens)->next)
		{
			hide_quotes(&((*tokens)->next));
			del = remove_quotes((*tokens)->next->token, g);
			prepare_del(&del);
		}
		else
			del = NULL;
		is_expand = is_expand_heredoc(del);
	}
	return (314);
}
