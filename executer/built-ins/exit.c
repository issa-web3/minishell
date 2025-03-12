/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/12 14:04:29 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **cmd, t_env **my_env, t_garbage **my_garbage)
{
	(void)cmd;
	(void)my_env;
	(void)my_garbage;
	write(1, "exit\n", 5);
	clear_garbage(my_garbage);
	clear_env(my_env);
	exit(EXIT_SUCCESS);
}
