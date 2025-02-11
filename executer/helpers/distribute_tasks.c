/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_tasks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:38:24 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/11 11:03:35 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	exec_by_idx(t_2_exec *data, t_env *my_env, t_garbage **my_garbage)
{
	char	*cmd;

	exec_builtin(data->cmd, my_env, my_garbage, 1);
	// not built-in
	cmd = data->cmd[0];
	data->cmd[0] = get_path(data->cmd[0], my_env, my_garbage);
	execve(data->cmd[0], data->cmd, NULL);
	// stderror please
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	clear_garbage(my_garbage);
	exit(EXIT_FAILURE);
}

void	distribute_tasks(t_process_info pi, pid_t (*pipes)[2], t_2_exec *data, t_env *my_env, t_garbage **my_garbage)
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
		while (--process_idx > 0)
			data = data->next;
		printf("%s, %s\n", data->infile, data->outfile);
		if (data->infile)
			ft_dup2(open(data->infile, O_RDONLY), STDIN_FILENO);
		if (data->outfile)
			ft_dup2(open(data->outfile, O_WRONLY | O_CREAT, 0777), STDOUT_FILENO);
		exec_by_idx(data, my_env, my_garbage);
		close(pipes[process_idx][0]);
		close(pipes[process_idx][1]);
	}
}
