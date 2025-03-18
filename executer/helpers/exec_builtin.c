/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:33 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/18 22:04:29 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	exec_builtin(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage, char is_child)
{
	t_builtin	built_in[7];
	int			i;

	built_in[0].name = "echo";
	built_in[0].func = ft_echo;
	built_in[1].name = "cd";
	built_in[1].func = ft_cd;
	built_in[2].name = "exit";
	built_in[2].func = ft_exit;
	built_in[3].name = "export";
	built_in[3].func = ft_export;
	built_in[4].name = "unset";
	built_in[4].func = ft_unset;
	built_in[5].name = "pwd";
	built_in[5].func = ft_pwd;
	built_in[6].name = "env";
	built_in[6].func = ft_env;
	i = 0;
	while (i < 7 && ft_strcmp(built_in[i].name, data->cmd[0]) != 0)
		i++;
	i++;
	if (!is_child)
		i = i * ((redirections(data->files, 0) + 1));
	if (i-- > 0)
	{
		if (i != 7)
		{
			(built_in[i].func)(data, my_env, my_garbage, is_child);
			if (is_child)
				(clear_env(my_env), clear_garbage(my_garbage), exit(EXIT_SUCCESS)); // built-in executed so get out
		}
	}
	else
		(set_exit_status(NO_SUCH_FILE_OR_DIR));
}
