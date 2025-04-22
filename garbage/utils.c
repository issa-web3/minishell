/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:23:38 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 14:53:44 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_garbage(t_garbage **my_garbage)
{
	t_garbage	*curr;
	t_garbage	*next;
	size_t		i;

	curr = *my_garbage;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	i = 3;
	while (i < 1024)
		close(i++);
	*my_garbage = NULL;
}

t_garbage	*init_node(t_garbage *new_g_n, void *ptr)
{
	if (new_g_n)
	{
		new_g_n->next = NULL;
		new_g_n->my_env = NULL;
		new_g_n->ptr = ptr;
	}
	return (new_g_n);
}

t_garbage	*append_garbage(t_garbage **my_garbage, void *ptr)
{
	t_garbage	*last_garbage;

	last_garbage = *my_garbage;
	if (last_garbage == NULL)
		return (init_node(*my_garbage = malloc(sizeof(t_garbage)), ptr));
	while (last_garbage && last_garbage->next)
		last_garbage = last_garbage->next;
	return (init_node(last_garbage->next = malloc(sizeof(t_garbage)), ptr));
}

void	remove_ptr_from_garbage(t_garbage **my_garbage, void *ptr)
{
	t_garbage	*curr;
	t_garbage	*prev;

	curr = *my_garbage;
	prev = NULL;
	while (curr && ptr)
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
