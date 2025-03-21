/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/21 17:13:27 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage, char is_child)
{
	(void)data;
	(void)my_env;
	if (!is_child)
	{
		write(1, "exit\n", 5);
		clear_all(my_garbage);
		exit(EXIT_SUCCESS);
	}
}
