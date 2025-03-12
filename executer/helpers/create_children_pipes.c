/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_children_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:51:46 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/12 14:34:29 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static int	redirect_input(pid_t (*pipes)[2], int idx)
{
	int	fail;

	close(pipes[idx][1]);
	fail = ft_dup2(pipes[idx][0], STDIN_FILENO) == -1;
	close(pipes[idx][0]);
	return (fail);
}

static int	redirect_output(pid_t (*pipes)[2], int idx)
{
	int	fail;

	close(pipes[idx][0]);
	fail = ft_dup2(pipes[idx][1], STDOUT_FILENO) == -1;
	close(pipes[idx][1]);
	return (fail);
}

int	create_children_pipes(pid_t (*pipes)[2], t_process_info *pi)
{
	int	fail;

	fail = 0;
	while (pi->process_idx < pi->process_num && pi->fork_response != 0 && !fail)
	{
		if (pi->process_idx != pi->process_num - 1)
			fail = ft_pipe(pipes[pi->process_idx]) == -1;
		pi->fork_response = ft_fork();
		fail |= pi->fork_response == -1;
		if (pi->fork_response == 0 && !fail)
		{
			if (pi->process_idx != 0)
				redirect_input(pipes, pi->process_idx - 1);
			if (pi->process_idx != pi->process_num - 1)
				redirect_output(pipes, pi->process_idx);
		}
		pi->process_idx++;
	}
	return (fail);
}
