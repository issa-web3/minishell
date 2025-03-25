/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/25 03:13:04 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	char	cwd[1024];
	char	*path;

	(void)my_env;
	(void)my_garbage;
	path = getcwd(cwd, sizeof(cwd));
	if (!path && !data->pwd)
	{
		perror("getcwd");
		return ;
	}
	else if (!path)
		path = data->pwd;
	printf("%s\n", path);
}
