/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_children_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:51:46 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/08 17:22:38 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	create_children_pipes(t_2_exec *data, t_env *my_env, pid_t (*pipes)[2], t_process_info *pi)
{
	int				fork_response;
	int				n;
	int				i;

	i = 0;
	n = pi->process_num;
	pipes = malloc(n * sizeof(pid_t[2])); // protection
	fork_response = 314;
	while (i < n && fork_response != 0)
	{
		if (i != n - 1)
			pipe(pipes[i]); // protection
		fork_response = fork(); // protection
		if (fork_response == 0)
		{
			if (i != 0)
			{
				close(pipes[i - 1][1]);
				if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
					perror("dup2");
				close(pipes[i - 1][0]);
			}
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
	pi->fork_response = fork_response;
	pi->process_idx = i;
}
