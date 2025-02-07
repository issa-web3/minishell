/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:01:06 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/07 11:16:53 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_by_idx(t_2_exec *data, char **env, int i)
{
	char	*cmd;

	while (--i >= 0)
		data = data->next;
	exec_builtin(data->cmd, env);
	printf("not buitl-in !! \n");
	// not built-in
	cmd = data->cmd[0];
	data->cmd[0] = get_path(data->cmd[0]);
	execve(data->cmd[0], data->cmd, NULL);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		perror("dup2");
	printf("%s: command not found\n", cmd);
}

void	execute(t_2_exec *data, char **env)
{
	pid_t	(*pipes)[2];
	pid_t	res;
	int		n;
	int		i;
	pid_t	*pids;

	// make kids
	i = 0;
	n = ft_lstsize(data);
	pipes = malloc(n * sizeof(pid_t[2])); // protection

	res = 314;
	
	while (i < n && res != 0)
	{
		if (i != n - 1)
			pipe(pipes[i]); // protection
		res = fork(); // protection
		
		// created child
		if (res == 0)
		{
			// read from pipe
			if (i != 0)
			{
				close(pipes[i - 1][1]);
				if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
					perror("dup2");
				close(pipes[i - 1][0]);
			}
			// write to pipe
			if (i != n - 1)
			{
				close(pipes[i][0]);
				if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
					perror("dup2");
				close(pipes[i][1]);
			}
		}
		i++;
	}
	
	for (int k = 0; k < i - 1; k++)
	{
		close(pipes[k][0]);
		close(pipes[k][1]);
	}
	
	// distribute tasks
	if (res != 0)
	{
		// parent
		i = 0;
		while (i < n - 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
		while (wait(NULL) != -1);
		// exit(EXIT_SUCCESS);
	}
	else
	{
		// children
		exec_by_idx(data, env, i - 1);
		close(pipes[i][0]);
		close(pipes[i][1]);
		exit(EXIT_FAILURE);
	}
}
