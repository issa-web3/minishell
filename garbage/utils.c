/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:23:38 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/21 17:23:34 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_garbage(t_garbage **my_garbage)
{
	t_garbage	*curr;
	t_garbage	*next;

	curr = *my_garbage;
	if (curr)
		curr = curr->next;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	free(*my_garbage);
	*my_garbage = NULL;
}

t_garbage	*append_garbage(t_garbage **my_garbage, void *ptr)
{
	t_garbage	*last_garbage;

	(void)ptr;
	last_garbage = *my_garbage;
	if (last_garbage == NULL)
		return (*my_garbage = malloc(sizeof(t_garbage)));
	while (last_garbage && last_garbage->next)
		last_garbage = last_garbage->next;
	return (last_garbage->next = malloc(sizeof(t_garbage)));
}
