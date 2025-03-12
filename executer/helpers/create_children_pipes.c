/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_children_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:51:46 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/12 13:49:02 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

int	create_children_pipes(pid_t (*pipes)[2], t_process_info *pi)
{
	int	fail;

	fail = 0;
	while (pi->process_idx < pi->process_num && pi->fork_response != 0 && !fail)
	{
		if (pi->process_idx != pi->process_num - 1)
			fail = ft_pipe(pipes[pi->process_idx]) == -1;
		pi->fork_response = ft_fork();
		if (pi->fork_response == -1 || fail)
			fail = 1;
		if (pi->fork_response == 0 && !fail)
		{
			if (pi->process_idx != 0)
			{
				close(pipes[pi->process_idx - 1][1]);
				fail = ft_dup2(pipes[pi->process_idx - 1][0], STDIN_FILENO) == -1;
				close(pipes[pi->process_idx - 1][0]);
			}
			if (pi->process_idx != pi->process_num - 1)
			{
				close(pipes[pi->process_idx][0]);
				fail = ft_dup2(pipes[pi->process_idx][1], STDOUT_FILENO) == -1;
				close(pipes[pi->process_idx][1]);
			}
		}
		pi->process_idx++;
	}
	return (fail);
}