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

int	ft_handle_heredoc(t_token **tokens, t_2_exec *node, t_garbage **g)
{
	char	*del;
	int		is_expand;

	while ((*tokens) && (*tokens)->type == HERE_DOC)
	{
		if ((*tokens)->next)
			del = (*tokens)->next->token;
		else
			del = NULL;
		is_expand = is_expand_heredoc(del);
		(void)is_expand;
		(void)node;
		(void)g;
	}
	return (314);
}
