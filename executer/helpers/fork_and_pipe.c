/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:56:20 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 14:54:33 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static int	redirect_input(t_pipe *pipes, int idx)
{
	int	fail;

	close(pipes[idx][1]);
	fail = ft_dup2(pipes[idx][0], STDIN_FILENO) == -1;
	close(pipes[idx][0]);
	return (fail);
}

static int	redirect_output(t_pipe *pipes, int idx)
{
	int	fail;

	close(pipes[idx][0]);
	fail = ft_dup2(pipes[idx][1], STDOUT_FILENO) == -1;
	close(pipes[idx][1]);
	return (fail);
}

void	fork_and_pipe(t_pipe *pipes, t_process_info *p_info,
		t_garbage **my_garbage)
{
	int	fail;

	fail = 0;
	while (p_info->process_idx < p_info->process_num
		&& p_info->fork_response != 0 && !fail)
	{
		if (p_info->process_idx != p_info->process_num - 1)
			fail = ft_pipe(pipes[p_info->process_idx]) == -1;
		p_info->fork_response = ft_fork();
		fail |= p_info->fork_response == -1;
		if (p_info->fork_response == 0 && !fail)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			if (p_info->process_idx != 0)
				fail |= redirect_input(pipes, p_info->process_idx - 1) == -1;
			if (p_info->process_idx != p_info->process_num - 1)
				fail |= redirect_output(pipes, p_info->process_idx) == -1;
		}
		p_info->process_idx++;
	}
	if (fail)
		(clear_all(my_garbage), set_and_exit(EXIT_FAILURE));
}
