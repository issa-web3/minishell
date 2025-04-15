/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:23:38 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/15 07:19:45 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_garbage(t_garbage **my_garbage)
{
	t_garbage	*curr;
	t_garbage	*next;

	curr = *my_garbage;
	if (curr)
	{
		free(curr->data->pwd);
		curr = curr->next;
	}
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
