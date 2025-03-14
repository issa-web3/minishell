/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:01:42 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/14 10:14:25 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_env	*ft_getenv(char *name, t_env **my_env)
{
	t_env	*curr;

	curr = *my_env;
	while (curr)
	{
		if (ft_strcmp(name, curr->name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
