/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:23:38 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 11:23:23 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	*ft_malloc(size_t size, t_garbage **my_garbage)
{
	t_garbage	*new_garbage;
	void		*allocated;

	allocated = malloc(size);
	if (allocated == NULL)
	{
		clear_garbage(my_garbage);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_garbage = append_garbage(my_garbage, allocated);
	if (new_garbage == NULL)
	{
		clear_garbage(my_garbage);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_garbage->ptr = allocated;
	new_garbage->next = NULL;
	return (allocated);
}
