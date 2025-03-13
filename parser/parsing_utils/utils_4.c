/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-13 12:48:44 by khoukouj          #+#    #+#             */
/*   Updated: 2025-03-13 12:48:44 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hide_quotes(t_token **node)
{
	int	i;

	i = 0;
	if ((*node) && (*node)->type == WORD)
	{
		while ((*node)->token[i])
		{
			if (is_quote((*node)->token[i]) == 1)
				(*node)->token[i] = -1;
			else if (is_quote((*node)->token[i]) == 2)
				(*node)->token[i] = -2;
			i++;
		}
	}
}

// t_token	*restore_quotes(t_token *lst)

