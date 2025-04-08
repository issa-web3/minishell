/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_children_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:51:46 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/08 15:37:20 by test             ###   ########.fr       */
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

int	create_children_pipes(t_pipe *pipes, t_process_info *p_info)
{
	int	fail;

	fail = 0;
	while (p_info->process_idx < p_info->process_num && p_info->fork_response != 0 && !fail)
	{
		fail = ft_pipe(pipes[p_info->process_idx]) == -1;
		p_info->fork_response = ft_fork();
		fail |= p_info->fork_response == -1;
		if (p_info->fork_response == 0 && !fail)
		{
			if (p_info->process_idx != 0)
				redirect_input(pipes, p_info->process_idx - 1);
			if (p_info->process_idx != p_info->process_num - 1)
				redirect_output(pipes, p_info->process_idx);
		}
		p_info->process_idx++;
	}
	return (fail);
}
