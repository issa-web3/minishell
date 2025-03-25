/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/25 02:44:51 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	char	cwd[1024];
	char	*success;

	(void)data;
	(void)my_env;
	(void)my_garbage;
	success = getcwd(cwd, sizeof(cwd));
	if (success)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	else
		write(2, "\n", 1);
}
