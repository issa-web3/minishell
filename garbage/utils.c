/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:23:38 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/17 16:35:35 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_garbage	*append_garbage(t_garbage **my_garbage)
{
	t_garbage	*last_garbage;

	last_garbage = *my_garbage;
	if (last_garbage == NULL)
		return (*my_garbage = malloc(sizeof(t_garbage)));
	while (last_garbage && last_garbage->next)
		last_garbage = last_garbage->next;
	return (last_garbage->next = malloc(sizeof(t_garbage)));
}

void	remove_ptr_from_garbage(t_garbage **my_garbage, void *ptr)
{
	t_garbage	*curr;
	t_garbage	*prev;

	curr = *my_garbage;
	prev = NULL;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev == NULL)
				*my_garbage = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}
