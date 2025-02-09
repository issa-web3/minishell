/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:23:38 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 13:41:02 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_garbage(t_garbage **my_garbage)
{
	t_garbage	*curr;
	t_garbage	*next;

	curr = *my_garbage;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	*my_garbage = NULL;
}

t_garbage	*append_garbage(t_garbage **my_garbage, void *ptr)
{
	t_garbage	*last_garbage;

	last_garbage = *my_garbage;
	if (last_garbage == NULL)
		return (*my_garbage = malloc(sizeof(t_garbage)));
	while (last_garbage && last_garbage->next)
		last_garbage = last_garbage->next;
	return (last_garbage->next = malloc(sizeof(t_garbage)));
}
