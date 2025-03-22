/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_prev_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:47:58 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/22 21:04:47 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	close_prev_pipes(t_pipe *pipes, int nth_process)
{
	int	i;

	i = 0;
	while (i < nth_process - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
