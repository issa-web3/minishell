/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:01:42 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/13 14:26:30 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_env	*ft_getenv(char *name, t_env **my_env)
{
	t_env	*curr;
	int		i;

	i = 0;
	curr = *my_env;
	while (curr)
	{
		if (ft_strcmp(name, curr->name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
