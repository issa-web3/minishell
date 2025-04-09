/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:04:01 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/08 15:37:35 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restore_hidden_q(char **del)
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

int	exec_heredoc(t_2_exec **node, t_token **tokens, char *del, t_garbage **g)
{
	// char	*file_name;
	char	*line;
	char	*res;
	// int		save_stdin;
	// int		is_expand;

	// is_expand = is_expand_heredoc(del);
	res = NULL;
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!ft_strcmp(line, del))
			break ;
		line = ft_strjoin(line, "\n", g);
		res = ft_strjoin(res, line, g);
	}
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next->next;
	else
		(*tokens) = (*tokens)->next;
	(void)node;
	return (1);
}

int	ft_handle_heredoc(t_token **tokens, t_2_exec **node, t_garbage **g)
{
	char	*del;

	if (!tokens || !(*tokens))
		return (1);
	if ((*tokens) && (*tokens)->type == HERE_DOC)
	{
		if ((*tokens)->next)
		{
			hide_quotes(&((*tokens)->next));
			del = remove_quotes((*tokens)->next->token, g);
			restore_hidden_q(&del);
		}
		else
			del = NULL;
		exec_heredoc(node, tokens, del, g);
	}
	return (0);
}
