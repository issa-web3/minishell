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
}

static int	create_cmd(t_token **tokens, t_2_exec **lst, t_2_exec *node, t_garbage **garbage)
{
	if ((*tokens) && (*tokens)->type == WORD)
	{
		ft_handle_cmd(&node, garbage, tokens);
		if (tokens == NULL)
		{
			ft_lstadd_back_t2exec(lst, node);
			return (1);
		}
	}
	return (1); // need to change this to 0 rn just for testing
}

t_2_exec	*ft_analyse(char *line, t_garbage **garbage)
{
	t_2_exec	*lst;
	t_2_exec	*node;
	t_token		*tokens;


	lst = NULL;
	tokens = ft_create_tokens(line, garbage);
	while (tokens)
	{
		node = ft_malloc(sizeof(t_2_exec), garbage);
		ft_init_2exec(node);
		while (tokens && tokens->type != PIPE)
		{
			if (create_cmd(&tokens, &lst, node, garbage))
				break ;
		}
		ft_lstadd_back_t2exec(&lst, node);
		if (tokens)
			tokens = tokens->next;
	}
	return (lst);
}