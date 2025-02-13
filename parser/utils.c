/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-13 09:05:47 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-13 09:05:47 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_tok_node(char *tok, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = tok;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_lst_addback(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new_token;
}
