/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-21 10:09:38 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-21 10:09:38 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_init_2exec(t_2_exec *node)
{
	node->cmd = NULL;
	node->appends = NULL;
	node->infiles = NULL;
	node->outfiles = NULL;
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
		file_node->type = (*tokens)->type;
		(*tokens) = (*tokens)->next;
	}
}

int	handle_redir(t_2_exec **node, t_token **tokens, t_garbage **garbage)
{
	t_file	*files;
	t_file	*file_node;

	files = NULL;
	if (tokens == NULL || *tokens == NULL)
		return (1);
	while ((*tokens) && ((*tokens)->type == REDIR_INPUT
		|| (*tokens)->type == REDIR_OUTPUT
		|| (*tokens)->type == APPEND))
	{
		file_node = ft_malloc(sizeof(t_file), garbage);
		fill_file_info(file_node, tokens, garbage);
		ft_lstadd_back_t_file(&files, file_node);
		if ((*tokens) && (*tokens)->type != PIPE)
			(*tokens) = (*tokens)->next;
	}
	(*node)->files = files;
	return (0);
}

t_2_exec	*ft_analyse(char *line, t_env *envl, t_garbage **garbage)
{
	t_2_exec	*lst;
	t_2_exec	*node;
	t_token		*tokens;


	lst = NULL;
	tokens = ft_create_tokens(line, envl, garbage);
	while (tokens)
	{
		node = ft_malloc(sizeof(t_2_exec), garbage);
		ft_init_2exec(node);
		while (tokens && tokens->type != PIPE)
		{
			if (create_cmd(&tokens, node, garbage))
				break;
			if (handle_redir(&node, &tokens, garbage))
				break ;
		}
		ft_lstadd_back_t2exec(&lst, node);
		if (tokens)
			tokens = tokens->next;
	}
	return (lst);
}
