/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_useless_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:56:14 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/15 10:56:15 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	close_useless_pipes(t_pipe *pipes, int nth_process)
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
