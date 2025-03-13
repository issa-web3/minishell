/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:01:06 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/13 13:59:20 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	execute(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	t_process_info	pi;
	int				fail;
	pid_t			(*pipes)[2];

	pi.process_idx = 0;
	pi.process_num = ft_lstsize(data);
	if (!data || !data->cmd || !data->cmd[0])
		return ;
	pipes = ft_malloc(pi.process_num * sizeof(pid_t[2]), my_garbage);
	pi.fork_response = 314;
	if (pi.process_num == 1 && (
			!ft_strcmp(data->cmd[0], "cd")
			|| !ft_strcmp(data->cmd[0], "exit")
			|| !ft_strcmp(data->cmd[0], "export")
			|| !ft_strcmp(data->cmd[0], "unset")
			|| !ft_strcmp(data->cmd[0], "pwd")
			|| !ft_strcmp(data->cmd[0], "env")
			|| !ft_strcmp(data->cmd[0], "echo")
		)
	)
		(exec_builtin(data, my_env, my_garbage, 0), pi.process_num--);
	fail = create_children_pipes(pipes, &pi);
	close_prev_pipes(pipes, pi.process_idx);
	while (pi.fork_response && wait(NULL) != -1)
		;
	if (fail)
		return ;
	distribute_tasks(pi, pipes, data, my_env, my_garbage);
}
