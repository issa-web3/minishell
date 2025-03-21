/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:33 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/21 00:44:46 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

// static void	init_struct(t_builtin (*built_in)[7], t_garbage **g)
// {
// 	built_in[0]->name = ft_strdup("echo", g);
// 	built_in[0]->func = ft_echo;
// 	built_in[1]->name = ft_strdup("cd", g);
// 	built_in[1]->func = ft_cd;
// 	built_in[2]->name = ft_strdup("exit", g);
// 	built_in[2]->func = ft_exit;
// 	built_in[3]->name = ft_strdup("export", g);
// 	built_in[3]->func = ft_export;
// 	built_in[4]->name = ft_strdup("unset", g);
// 	built_in[4]->func = ft_unset;
// 	built_in[5]->name = ft_strdup("pwd", g);
// 	built_in[5]->func = ft_pwd;
// 	built_in[6]->name = ft_strdup("env", g);
// 	built_in[6]->func = ft_env;
// }

int	exec_builtin(t_2_exec *data, t_env **my_env,
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
	// init_struct(&built_in, my_garbage);
	i = 0;
	while (i < 7 && ft_strcmp(built_in[i].name, data->cmd[0]) != 0)
		i++;
	if (i != 7)
	{
		set_exit_status(SUCCESS);
		if (redirections(&data->files, 0) != -1)
			(built_in[i].func)(data, my_env, my_garbage, is_child);
		return (0);
	}
	return (-1);
}
