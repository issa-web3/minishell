/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:04:01 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/09 13:41:17 by ioulkhir         ###   ########.fr       */
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

// static int	create_heredoc_buffer(char **res, char *line, int is_expand, t_garbage **g) // remember to create a struct contains line and is expand flag
// {
// 	if (is_expand)
// 	{
// 		line = ft_strjoin(ft_replace_dollar())
// 	}
// }

int	exec_heredoc(t_2_exec **node, char *del, t_garbage **g)
{
	// char	*file_name;
	char	*res;
	// int		save_stdin;
	t_heredoc	info;


	info.is_expand = is_expand_heredoc(del);
	res = NULL;
	while (1)
	{
		info.line = readline(">");
		if (!info.line)
			break ;
		if (!ft_strcmp(info.line, del))
			break ;
		info.line = ft_strjoin(info.line, "\n", g);
		res = ft_strjoin(res, info.line, g);
	}
	(void)node;
	return (1);
}

int	ft_handle_heredoc(t_token **tokens, t_2_exec **node, t_env *env, t_garbage **g)
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
		exec_heredoc(node, del, g);
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next->next;
		else
			(*tokens) = (*tokens)->next;
	}
	(void)env;
	return (0);
}
