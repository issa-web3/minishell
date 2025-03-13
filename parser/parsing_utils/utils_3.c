/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-27 13:16:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-27 13:16:53 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_var(int c)
{
	return (ft_isalnum(c) || c == '_');
}

t_token	*ft_lstlast_token(t_token *lst)
{
	t_token	*current;

	if (!lst)
		return (lst);
	current = lst;
	while (current->next)
		current = current->next;
	return current;
}

t_token	*new_token_node(char *str, int type, t_garbage **garbage)
{
	t_token	*node;

	node = ft_malloc(sizeof(t_token), garbage);
	node->token = ft_strdup(str, garbage);
	node->type = type;
	node->next = NULL;
	return (node);
}

int	to_expand(t_token **node, t_env *env, t_garbage **g)
{
	if (can_i_expand((*node)->token))
		ft_expand_token(node, env, g);
	return (1);
}
