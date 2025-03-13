/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/13 10:12:14 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child)
{
	(void)data;
	(void)my_env;
	(void)my_garbage;
	if (!is_child)
		write(1, "exit\n", 5);
	clear_garbage(my_garbage);
	clear_env(my_env);
	exit(EXIT_SUCCESS);
}
