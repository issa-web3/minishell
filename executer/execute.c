/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:01:06 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/08 14:10:35 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	execute(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	t_process_info	p_info;
	int				fail;
	int				status;
	t_pipe			*pipes;

	set_exit_status(SUCCESS);
	p_info.process_idx = 0;
	p_info.process_num = ft_lstsize(data);
	pipes = ft_malloc(p_info.process_num * sizeof(pid_t[2]), my_garbage);
	data->pipes = pipes;
	p_info.fork_response = 314;
	data->p_info = p_info;
	if (p_info.process_num == 1 && data->cmd && data->cmd[0] && (
			!ft_strcmp(data->cmd[0], "cd")
			|| !ft_strcmp(data->cmd[0], "exit")
			|| (!ft_strcmp(data->cmd[0], "export") && data->cmd[1])
			|| (!ft_strcmp(data->cmd[0], "unset"))
			// || !ft_strcmp(data->cmd[0], "env")
			// || !ft_strcmp(data->cmd[0], "pwd")
			// || !ft_strcmp(data->cmd[0], "echo")
		)
	)
		(exec_builtin(data, my_env, my_garbage), p_info.process_num--);
	fail = create_children_pipes(pipes, &p_info);
	close_prev_pipes(pipes, p_info.process_idx);
	status = 0;
	if (p_info.fork_response)
		waitpid(p_info.fork_response, &status, 0);
	while (p_info.fork_response && wait(NULL) != -1)
		;
	if (fail)
		return ;
	set_exit_status(status / 256);
	data->p_info = p_info;
	distribute_tasks(p_info, pipes, data, my_env, my_garbage);
}
