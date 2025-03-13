/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/13 10:23:53 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child)
{
	t_env	*to_rm;
	int		i;

	i = 1;
	(void)my_garbage;
	(void)is_child;
	while (data->cmd[i])
	{
		if (*my_env == NULL && !strcmp(data->cmd[i], "PATH"))
		{
			if (*(data->default_path))
				free(*(data->default_path));
			*(data->default_path) = NULL;
		}
		to_rm = ft_getenv(data->cmd[i], my_env);
		del_env_var(to_rm, my_env);
		i++;
	}
}
