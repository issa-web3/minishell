/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_prev_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:47:58 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/12 07:42:21 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	close_prev_pipes(pid_t (*pipes)[2], int nth_process)
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
