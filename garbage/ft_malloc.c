/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:23:38 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/21 17:26:45 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t size, t_garbage **my_garbage)
{
	t_garbage	*new_garbage;
	void		*allocated;

	allocated = malloc(size);
	if (allocated == NULL)
	{
		perror("malloc");
		clear_all(my_garbage);
		exit(EXIT_FAILURE);
	}
	new_garbage = append_garbage(my_garbage, allocated);
	if (new_garbage == NULL)
	{
		perror("malloc");
		clear_all(my_garbage);
		exit(EXIT_FAILURE);
	}
	new_garbage->ptr = allocated;
	new_garbage->next = NULL;
	return (allocated);
}
