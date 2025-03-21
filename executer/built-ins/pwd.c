/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/21 00:35:30 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage, char is_child)
{
	char	cwd[1024];

	(void)data;
	(void)is_child;
	(void)my_env;
	(void)my_garbage;
	getcwd(cwd, sizeof(cwd));
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
}
