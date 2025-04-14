/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:01:06 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/14 15:22:18 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	update_pwd(t_2_exec *data, t_garbage **my_garbage, char *new)
{
	static char	pwd[1024];
	static char	*pwd_copy;
	static char	flag;

	if (new)
	{
		pwd_copy = new;
		data->pwd = pwd_copy;
		ft_strlcpy(pwd, data->pwd, ft_strlen(data->pwd) + 1);
		flag = 1;
	}
	if (flag)
		flag = 0;
	pwd_copy = ft_strdup(pwd, my_garbage);
	if (!new && !flag && getcwd(pwd, 1024))
		pwd_copy = ft_strdup(pwd, my_garbage);
	data->pwd = pwd_copy;
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
	int				fail;
	t_pipe			*pipes;

	update_pwd(data, my_garbage, NULL);
	set_exit_status(EXIT_SUCCESS);
	
	p_info.process_idx = 0;
	p_info.fork_response = 314;
	p_info.process_num = ft_lstsize(data);

	pipes = ft_malloc((p_info.process_num - 1) * sizeof(t_pipe), my_garbage);
	data->pipes = pipes;
	data->p_info = p_info;
	if (is_a_parent_task(data, p_info))
		(exec_builtin(data, my_env, my_garbage), p_info.process_num--);
	fail = fork_and_pipe(pipes, &p_info);
	if (fail)
		return (clear_all(my_garbage), set_and_exit(EXIT_FAILURE));
	if (p_info.process_num != 0)
	{
		close_useless_pipes(pipes, p_info.process_idx);
		if (p_info.fork_response)
		{
			// wait_last_pid(p_info.fork_response);
			while (wait(NULL) != -1)
				;
		}
		data->p_info = p_info;
		execute_task_by_idx(pipes, data, my_env, my_garbage);
	}
}
