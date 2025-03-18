/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_tasks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:38:24 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/18 22:12:10 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

char	redirections(t_file *files, char redirect)
{
	int	fd;
	int	file_mode;

	while (files)
	{
		if (files->name == NULL)
			return (-2);
		file_mode = 0;
		file_mode += (files->type == IN_FILE) * O_RDONLY;
		file_mode += (files->type == OUT_FILE) * (O_WRONLY | O_CREAT | O_TRUNC);
		file_mode += (files->type == APPEND_FILE)
			* (O_WRONLY | O_CREAT | O_APPEND);
		fd = ft_open(files->name, file_mode);
		if (fd == -1 || (redirect && ft_dup2(fd, files->type != IN_FILE) == -1))
			return (-2);
		close(fd);
		files = files->next;
	}
	return (0);
}

void	exec_by_idx(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	exec_builtin(data, my_env, my_garbage, 1);
	data->cmd[0] = get_path(data, my_env, my_garbage);
	execve(data->cmd[0], data->cmd, format_env(my_env, my_garbage));
	perror("execve");
	clear_garbage(my_garbage);
	exit(EXIT_FAILURE);
}

static void	redirect_and_execute(t_2_exec *data, int process_idx,
		t_env **my_env, t_garbage **my_garbage)
{
	while (--process_idx > 0)
		data = data->next;
	if (redirections(data->files, 1) != -2)
		exec_by_idx(data, my_env, my_garbage);
	
}

void	distribute_tasks(t_process_info pi, pid_t (*pipes)[2], t_2_exec *data,
		t_env **my_env, t_garbage **my_garbage)
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
	}
	else
	{
		redirect_and_execute(data, process_idx, my_env, my_garbage);
		close(pipes[process_idx][0]);
		close(pipes[process_idx][1]);
		clear_garbage(my_garbage);
		clear_env(my_env);
		exit(EXIT_FAILURE);
	}
}
