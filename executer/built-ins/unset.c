/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:56:00 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/17 16:09:47 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	t_env	*to_rm;
	int		i;

	i = 1;
	(void)my_garbage;
	while (data->cmd[i])
	{
		if (!ft_strcmp(data->cmd[i], "PATH"))
			*(data->default_path) = NULL;
		to_rm = ft_getenv(data->cmd[i], my_env);
		del_env_var(to_rm, my_env);
		i++;
	}
}
