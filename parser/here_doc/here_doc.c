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

static void	restore_fds(int save_stdin)
{
	ft_dup2(save_stdin, 0);
	close(save_stdin);
}

static void	create_heredoc_buffer(char **res, t_heredoc *info,
		t_garbage **g, t_env *env)
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
	free(info->line);
	info->line = NULL;
}

int	exec_heredoc(t_2_exec **node, t_heredoc *info, t_garbage **g, t_env *env)
{
	int			save_stdin;
	char		*res;
	t_file		*heredoc_node;

	1 && (res = NULL, save_stdin = ft_dup(0), g_signals = 3);
	while (1)
	{
		info->line = readline(">");
		if (!info->line || g_signals == 4)
			break ;
		if (!ft_strcmp(info->line, info->del))
			break ;
		create_heredoc_buffer(&res, info, g, env);
	}
	free(info->line);
	restore_fds(save_stdin);
	if (g_signals == 4)
		return (set_exit_status(TERMINATED_BY_CNTL_C), -1);
	create_heredoc_node(&heredoc_node, g, res);
	if (!(*node)->files)
		(*node)->files = heredoc_node;
	else
		ft_lstlast_file((*node)->files)->next = heredoc_node;
	return (1);
}

int	ft_handle_heredoc(t_token **tokens, t_2_exec **node,
		t_env *env, t_garbage **g)
{
	t_heredoc	info;

	if (!tokens || !(*tokens))
		return (1);
	if ((*tokens) && (*tokens)->type == HERE_DOC)
	{
		if ((*tokens)->next)
		{
			info.is_expand = is_expand_heredoc((*tokens)->next->token);
			hide_quotes(&((*tokens)->next));
			info.del = remove_quotes((*tokens)->next->token, g);
			restore_hidden_q(&info.del);
		}
		else
			info.del = NULL;
		if (exec_heredoc(node, &info, g, env) == -1)
			return (-1);
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next->next;
		else
			(*tokens) = (*tokens)->next;
	}
	return (0);
}
