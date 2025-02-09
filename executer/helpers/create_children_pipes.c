/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_children_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:51:46 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 09:48:50 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	create_children_pipes(t_2_exec *data, t_env *my_env, pid_t (*pipes)[2], t_process_info *pi)
{
	while (pi->process_idx < pi->process_num && pi->fork_response != 0)
	{
		if (pi->process_idx != pi->process_num - 1)
			pipe(pipes[pi->process_idx]); // protection
		pi->fork_response = fork(); // protection
		if (pi->fork_response == 0)
		{
			if (pi->process_idx != 0)
			{
				close(pipes[pi->process_idx - 1][1]);
				if (dup2(pipes[pi->process_idx - 1][0], STDIN_FILENO) == -1)
					perror("dup2");
				close(pipes[pi->process_idx - 1][0]);
			}
			if (pi->process_idx != pi->process_num - 1)
			{
				close(pipes[pi->process_idx][0]);
				if (dup2(pipes[pi->process_idx][1], STDOUT_FILENO) == -1)
					perror("dup2");
				close(pipes[pi->process_idx][1]);
			}
		}
		pi->process_idx++;
	}
}