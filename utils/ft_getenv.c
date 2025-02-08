/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:01:42 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/08 10:51:25 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_env	*ft_getenv(char *name, t_env *my_env)
{
	int	i;

	i = 0;
	while (my_env)
	{
		if (ft_strcmp(name, my_env->name) == 0)
			return (my_env);
		my_env = my_env->next;
	}
	return (NULL);
}
