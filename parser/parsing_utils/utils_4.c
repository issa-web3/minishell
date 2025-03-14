/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:48:44 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/14 08:00:57 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hide_quotes(t_token **node)
{
	int	i;

	i = 0;
	if ((*node) && (*node)->type == WORD)
	{
		while ((*node)->token && (*node)->token[i])
		{
			if (is_quote((*node)->token[i]) == 1)
				(*node)->token[i] = -1;
			else if (is_quote((*node)->token[i]) == 2)
				(*node)->token[i] = -2;
			i++;
		}
	}
}

t_token	*restore_quotes(t_token *lst)
{
	int		i;
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->type == WORD)
		{
			i = 0;
			while (curr->token && curr->token[i])
			{
				if (is_hquote(curr->token[i]) == 1)
					curr->token[i] = '\'';
				else if (is_hquote(curr->token[i]) == 2)
					curr->token[i] = '"';
				i++;
			}
		}
		curr = curr->next;
	}
	return (lst);
}
