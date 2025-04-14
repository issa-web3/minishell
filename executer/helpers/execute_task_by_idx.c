/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_task_by_idx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:38:24 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/09 10:44:00 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

char	redirections(t_file **files, char redirect)
{
	int		fd;
	int		file_mode;
	t_file	*curr;

	curr = *files;
	while (curr)
	{
		if (curr->name == NULL)
			return (set_exit_status(NO_SUCH_FILE_OR_DIR), -1);
		file_mode = 0;
		file_mode += (curr->type == IN_FILE) * O_RDONLY;
		file_mode += (curr->type == OUT_FILE) * (O_WRONLY | O_CREAT | O_TRUNC);
		file_mode += (curr->type == APPEND_FILE)
			* (O_WRONLY | O_CREAT | O_APPEND);
		fd = ft_open(curr->name, file_mode);
		if (fd == -1 || (redirect && ft_dup2(fd, curr->type != IN_FILE) == -1))
			return (set_exit_status(NO_SUCH_FILE_OR_DIR), -1);
		close(fd);
		curr = curr->next;
	}
	*files = NULL;
	return (0);
}

void	exec_by_idx(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	char	*cmd;

	if (exec_builtin(data, my_env, my_garbage) == -1)
	{
		set_exit_status(EXIT_SUCCESS);
		cmd = get_path(data, my_env, my_garbage);
		if (cmd)
			execve(cmd, data->cmd, format_env(my_env, my_garbage));
	}
}

static void	redirect_and_execute(t_2_exec *data, int process_idx,
		t_env **my_env, t_garbage **my_garbage)
{
	while (--process_idx > 0)
		data = data->next;
	if (redirections(&data->files, 1) != -1)
		exec_by_idx(data, my_env, my_garbage);
}

void	execute_task_by_idx(t_pipe *pipes, t_2_exec *data,
		t_env **my_env, t_garbage **my_garbage)
{
	t_process_info	p_info;
	int				process_idx;
	int				process_num;
	int				fork_response;

	p_info = data->p_info;
	process_idx = p_info.process_idx;
	process_num = p_info.process_num;
	fork_response = p_info.fork_response;
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
		clear_all(my_garbage);
		exit(get_exit_status());
	}
}
