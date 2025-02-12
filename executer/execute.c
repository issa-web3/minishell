/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:01:06 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/12 08:27:57 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	execute(t_2_exec *data, t_env *my_env, t_garbage **my_garbage)
{
	pid_t			(*pipes)[2];
	t_process_info	pi;
	pid_t			*pids;
	int				fail;

	// make kids
	pi.process_idx = 0;
	pi.process_num = ft_lstsize(data);
	if (data && data->cmd[0] == 0)
		return ;
	pipes = ft_malloc(pi.process_num * sizeof(pid_t[2]), my_garbage); // protection
	pi.fork_response = 314;
	if (pi.process_num == 1 && (
				!ft_strcmp(data->cmd[0], "cd")
				|| !ft_strcmp(data->cmd[0], "exit")
				|| !ft_strcmp(data->cmd[0], "export")
				|| !ft_strcmp(data->cmd[0], "unset")
				|| !ft_strcmp(data->cmd[0], "clear")
			)
		)
		(exec_builtin(data->cmd, my_env, my_garbage, 0), pi.process_num--);
	fail = create_children_pipes(data, my_env, pipes, &pi);
	close_prev_pipes(pipes, pi.process_idx);
	if (fail && pi.fork_response == 0)
	{
		clear_garbage(my_garbage);
		exit(EXIT_FAILURE);
	}
	else if (fail)
		return ;
	distribute_tasks(pi, pipes, data, my_env, my_garbage);
}
