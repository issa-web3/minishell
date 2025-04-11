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

static void	create_heredoc_buffer(char **res, t_heredoc *info, t_garbage **g, t_env *env) // remember to create a struct contains line and is expand flag
{
	char	*line;

	line = NULL;
	if (info->is_expand)
	{
		line = ft_strjoin(ft_replace_dollar(info->line, env, g), "\n", g);
		*res = ft_strjoin(*res, line, g);
	}
	else
	{
		line = ft_strjoin(info->line, "\n", g);
		*res = ft_strjoin(*res, line, g);
	}
}

int	exec_heredoc(t_2_exec **node, t_heredoc *info, t_garbage **g, t_env *env)
{
	// int			save_stdin;
	char		*res;
	t_file		*heredoc_node;
	char		*file_name;

	res = NULL;
	while (1)
	{
		info->line = readline(">");
		if (!info->line)
			break ;
		if (!ft_strcmp(info->line, info->del))
			break ;
		create_heredoc_buffer(&res, info, g, env);
	}
	file_name = generate_file_name(g);
	heredoc_node = new_file_node(file_name, g, res);
	if (!(*node)->files)
		(*node)->files = heredoc_node;
	else
		ft_lstlast_file((*node)->files)->next = heredoc_node;
	return (1);
}

int	ft_handle_heredoc(t_token **tokens, t_2_exec **node, t_env *env, t_garbage **g)
{
	t_heredoc info;

	if (!tokens || !(*tokens))
		return (1);
	if ((*tokens) && (*tokens)->type == HERE_DOC)
	{
		info.is_expand = is_expand_heredoc((*tokens)->next->token);
		if ((*tokens)->next)
		{
			hide_quotes(&((*tokens)->next));
			info.del = remove_quotes((*tokens)->next->token, g);
			restore_hidden_q(&info.del);
		}
		else
			info.del = NULL;
		exec_heredoc(node, &info, g, env);
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next->next;
		else
			(*tokens) = (*tokens)->next;
	}
	return (0);
}
