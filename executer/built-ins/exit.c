/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/26 02:53:06 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	int		exit_status;

	exit_status = 0;
	(void)my_env;
	if (data->pi.fork_response == 314)
		write(1, "exit\n", 5);
	clear_all(my_garbage);
	set_exit_status(SUCCESS);
	exit(exit_status);
}
