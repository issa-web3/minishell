/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:22:27 by test              #+#    #+#             */
/*   Updated: 2025/03/21 16:51:52 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_all(t_garbage **my_garbage)
{
	pid_t			(*pipes)[2];
	int				process_idx;
	t_2_exec		*data;
	t_env			**my_env;

	if ((*my_garbage))
	{
		data = (*my_garbage)->data;
		my_env = (*my_garbage)->my_env;
		if (data)
		{
			process_idx = data->pi.process_idx;
			pipes = data->pipes;
			close(pipes[process_idx][0]);
			close(pipes[process_idx][1]);
		}
		clear_env(my_env);
	}
	clear_garbage(my_garbage);
}
