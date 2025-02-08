/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_tasks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:38:24 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/08 15:55:38 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	exec_by_idx(t_2_exec *data, t_env *my_env, int i)
{
	char	*cmd;

	while (--i >= 0)
		data = data->next;
	exec_builtin(data->cmd, my_env, 1);
	// not built-in
	cmd = data->cmd[0];
	data->cmd[0] = get_path(data->cmd[0], my_env);
	execve(data->cmd[0], data->cmd, NULL);
	// stderror please
	printf("%s: command not found\n", cmd);
}

void	distribute_tasks(t_process_info pi, pid_t (*pipes)[2], t_2_exec *data, t_env *my_env)
{
	int		process_idx;
	int		process_num;
	int		fork_response;

	process_idx = pi.process_idx;
	process_num = pi.process_num;
	fork_response = pi.fork_response;
	if (fork_response != 0)
	{
		process_idx = 0;
		while (process_idx < process_num - 1)
		{
			close(pipes[process_idx][0]);
			close(pipes[process_idx][1]);
			process_idx++;
		}
		while (wait(NULL) != -1);
	}
	else
	{
		exec_by_idx(data, my_env, process_idx - 1);
		close(pipes[process_idx][0]);
		close(pipes[process_idx][1]);
		exit(EXIT_FAILURE);
	}
}
