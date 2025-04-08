/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/08 18:13:42 by ioulkhir         ###   ########.fr       */
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
		set_exit_status(EXIT_FAILURE);
		return ;
	}
	else if (!path)
		path = data->pwd;
	printf("%s\n", path);
}
