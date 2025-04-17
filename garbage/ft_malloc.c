/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:23:38 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/17 17:49:38 by ioulkhir         ###   ########.fr       */
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
		set_and_exit(EXIT_FAILURE);
	}
	new_garbage = append_garbage(my_garbage, allocated);
	if (new_garbage == NULL)
	{
		perror("malloc");
		clear_all(my_garbage);
		set_and_exit(EXIT_FAILURE);
	}
	return (allocated);
}
