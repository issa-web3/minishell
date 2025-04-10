/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:22:27 by test              #+#    #+#             */
/*   Updated: 2025/04/10 10:33:56 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_all(t_garbage **my_garbage)
{
	t_pipe			*pipes;
	int				process_idx;
	t_2_exec		*data;
	t_env			**my_env;

	if ((*my_garbage))
	{
		data = (*my_garbage)->data;
		my_env = (*my_garbage)->my_env;
		if (data)
		{
			process_idx = data->p_info.process_idx - 1;
			pipes = data->pipes;
			if (pipes)
			{
				close(pipes[process_idx][0]);
				close(pipes[process_idx][1]);
			}
		}
		clear_env(my_env);
	}
	clear_garbage(my_garbage);
}
