/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:25:35 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/12 13:47:49 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	if (g_signals == 1)
	{
		(void)sig;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		set_exit_status(TERMINATED_BY_CNTL_C);
	}
	else if (g_signals == 3)
	{
		g_signals = 4;
		close(0);
		write(1, "\n", 1);
	}
}

