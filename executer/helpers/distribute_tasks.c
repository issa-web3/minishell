/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_tasks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:38:24 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/11 13:27:47 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

char	redirections(char *infile, char *outfile)
{
	int		fd_in;
	int		fd_out;
	char	success;

	if (infile)
	{
		fd_in = open(infile, O_RDONLY);
		if (fd_in == -1)
			return (perror(infile), 0);
		if (ft_dup2(fd_in, STDIN_FILENO) == -1)
			return (0);
		close(fd_in);
	}
	if (outfile)
	{
		fd_out = open(outfile, O_WRONLY | O_CREAT, 0777);
		if (fd_in == -1)
			return (perror(outfile), 0);
		if (ft_dup2(fd_out, STDOUT_FILENO) == -1)
			return (0);
		close(fd_out);
	}
	return (1);
}

void	exec_by_idx(t_2_exec *data, t_env *my_env, t_garbage **my_garbage)
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

void	distribute_tasks(t_process_info pi, pid_t (*pipes)[2], t_2_exec *data, t_env *my_env, t_garbage **my_garbage)
{
	int		process_idx;
	int		process_num;
	int		fork_response;
	char	success;

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
		success = redirections(data->infile, data->outfile);
		if (success)
			exec_by_idx(data, my_env, my_garbage);
		close(pipes[process_idx][0]);
		close(pipes[process_idx][1]);
		clear_garbage(my_garbage);
		exit(EXIT_FAILURE);
	}
}
