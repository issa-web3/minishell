/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:01:06 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 16:54:18 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	update_pwd(t_2_exec *data, t_garbage **my_garbage)
{
	static char	pwd[1024];

	data->pwd = ft_strdup(pwd, my_garbage);
	if (getcwd(pwd, 1024))
		data->pwd = ft_strdup(pwd, my_garbage);
	ft_strlcpy(pwd, data->pwd, ft_strlen(data->pwd) + 1);
}

int	is_a_parent_task(t_2_exec *data, t_process_info p_info)
{
	return (p_info.process_num == 1 && data->cmd && data->cmd[0] && (
			!ft_strcmp(data->cmd[0], "cd")
			|| !ft_strcmp(data->cmd[0], "exit")
			|| (!ft_strcmp(data->cmd[0], "export") && data->cmd[1])
			|| (!ft_strcmp(data->cmd[0], "unset"))
		)
	);
}

void	execute(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	t_process_info	p_info;
	t_pipe			*pipes;

	update_pwd(data, my_garbage);
	p_info.process_idx = 0;
	p_info.fork_response = 314;
	p_info.process_num = ft_lstsize(data);
	pipes = ft_malloc((p_info.process_num - 1) * sizeof(t_pipe), my_garbage);
	data->p_info = p_info;
	if (is_a_parent_task(data, p_info))
		(exec_builtin(data, my_env, my_garbage), p_info.process_num = 0);
	fork_and_pipe(pipes, &p_info, my_garbage);
	close_useless_pipes(pipes, p_info.process_idx);
	if (p_info.process_num == 0)
		return ;
	wait_children(p_info.fork_response);
	data->p_info = p_info;
	execute_task_by_idx(pipes, data, my_env, my_garbage);
}
