/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:09:38 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/12 01:28:46 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_init_2exec(t_2_exec *node)
{
	node->cmd = NULL;
	node->files = NULL;
}

static int	create_cmd(t_token **tokens, t_2_exec *node, t_garbage **garbage)
{
	if ((*tokens) && (*tokens)->type == WORD)
	{
		ft_handle_cmd(&node, garbage, tokens);
		if (!(*tokens))
			return (1);
	}
	return (0);
}

void	fill_file_info(t_file *file_node, t_token **tokens, t_garbage **garbage)
{
	if ((*tokens)->next && ((*tokens)->type == REDIR_INPUT
			|| (*tokens)->type == REDIR_OUTPUT || (*tokens)->type == APPEND))
	{
		file_node->name = ft_strdup((*tokens)->next->token, garbage);
		if ((*tokens)->type == REDIR_INPUT)
			file_node->type = IN_FILE;
		else if ((*tokens)->type == REDIR_OUTPUT)
			file_node->type = OUT_FILE;
		else
			file_node->type = APPEND_FILE;
		(*tokens) = (*tokens)->next;
	}
}

int	handle_redir(t_2_exec **node, t_token **tokens, t_garbage **garbage)
{
	t_file	*files;
	t_file	*file_node;
	int		a_r_found;

	files = NULL;
	a_r_found = 0;
	if (tokens == NULL || *tokens == NULL)
		return (1);
	while ((*tokens) && ((*tokens)->type == REDIR_INPUT
			|| (*tokens)->type == REDIR_OUTPUT
			|| (*tokens)->type == APPEND))
	{
		if ((*tokens)->next->token == NULL)
			a_r_found++;
		file_node = ft_malloc(sizeof(t_file), garbage);
		fill_file_info(file_node, tokens, garbage);
		ft_lstadd_back_t_file(&files, file_node);
		if ((*tokens) && (*tokens)->type != PIPE)
			(*tokens) = (*tokens)->next;
	}
	(*node)->files = files;
	if (a_r_found)
		return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), 1);
	return (0);
}

t_2_exec	*ft_analyse(char *line, t_env *envl, t_garbage **garbage)
{
	t_2_exec	*lst;
	t_2_exec	*node;
	t_token		*tokens;

	lst = NULL;
	tokens = ft_create_tokens(line, envl, garbage);
	tokens = remove_quotes_from_toks(tokens, garbage);
	restore_quotes(&tokens);
	while (tokens)
	{
		node = ft_malloc(sizeof(t_2_exec), garbage);
		ft_init_2exec(node);
		while (tokens && tokens->type != PIPE)
		{
			if (handle_redir(&node, &tokens, garbage))
				break ;
			if (create_cmd(&tokens, node, garbage))
				break ;
		}
		ft_lstadd_back_t2exec(&lst, node);
		if (tokens)
			tokens = tokens->next;
	}
	return (lst);
}
