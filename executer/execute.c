/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:01:06 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/05 17:07:35 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_by_idx(t_2_exec *data, int i)
{
	while (--i >= 0)
		data = data->next;
	execve(data->cmd[0], data->cmd, NULL);
	perror("execv");
}

void	execute(t_2_exec *data)
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
			else
			{
				close(pipes[i][1]);
				close(pipes[i][0]);
			}
		}
		i++;
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
		exec_by_idx(data, i - 1);
		close(pipes[i][0]);
		close(pipes[i][1]);
		exit(EXIT_FAILURE);
	}
}
