/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_tasks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:38:24 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/11 23:36:17 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

char	redirections(t_file *files, t_garbage **my_garbage)
{
	int	fd;
	int	file_mode;

	while (files != NULL)
	{
		file_mode = 0;
		file_mode = (files->type == IN_FILE) * O_RDONLY;
		file_mode = (files->type == OUT_FILE) * (O_WRONLY | O_CREAT | O_TRUNC);
		file_mode = (files->type == APPEND_FILE) * (O_WRONLY | O_CREAT | O_APPEND);
		fd = ft_open(files->name, file_mode);
		if (fd == -1 || ft_dup2(fd, files->type != IN_FILE) == -1)
			return (-1);
		close(fd);
		files = files->next;
	}
	return (0);
}

void	exec_by_idx(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	char	*cmd;

	exec_builtin(data->cmd, my_env, my_garbage, 1);
	cmd = data->cmd[0];
	data->cmd[0] = get_path(data->cmd[0], my_env, my_garbage);
	execve(data->cmd[0], data->cmd, NULL);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	clear_garbage(my_garbage);
	exit(EXIT_FAILURE);
}

void	distribute_tasks(t_process_info pi, pid_t (*pipes)[2], t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	int		tmp;
	int		process_idx;
	int		process_num;
	int		fork_response;
	char	result;

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
		tmp = process_idx;
		while (--process_idx > 0)
			data = data->next;
		result = redirections(data->files, my_garbage);
		if (result != -1)
			exec_by_idx(data, my_env, my_garbage);
		close(pipes[tmp][0]);
		close(pipes[tmp][1]);
		clear_garbage(my_garbage);
		exit(EXIT_FAILURE);
	}
}
