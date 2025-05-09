/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/19 16:03:56 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_new_pwd(t_2_exec *data, char *pwd, t_env **my_env,
		t_garbage **gc)
{
	char	*new_pwd;
	t_env	*env_tmp;

	if (data->cmd[1] == NULL)
	{
		env_tmp = ft_getenv("HOME", my_env);
		if (env_tmp == NULL)
			return (write(2, "cd: HOME not set\n", 17),
				set_exit_status(GENERIC_ERR), NULL);
		new_pwd = env_tmp->value;
	}
	else if (data->cmd[2])
		return (write(2, "cd: too many arguments\n", 23),
			set_exit_status(GENERIC_ERR), NULL);
	else if (data->cmd[1][0] == '/')
		new_pwd = data->cmd[1];
	else
		new_pwd = ft_strjoin(ft_strjoin(pwd, "/", gc), data->cmd[1], gc);
	return (new_pwd);
}

void	handle_failure(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL && ft_strcmp(data->cmd[1], "/"))
	{
		write(2, "cd: error retrieving current directory: ", 40);
		write(2, "getcwd: cannot access parent directories", 40);
		write(2, ": No such file or directory\n", 28);
		data->cmd = ft_split("cd /", ' ', my_garbage);
		ft_cd(data, my_env, my_garbage);
		return ;
	}
	free(pwd);
	set_exit_status(NO_SUCH_FILE_OR_DIR);
	perror(ft_strjoin("cd: ", data->cmd[1], my_garbage));
}

void	ft_cd(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	char	*new_pwd;
	char	*old_pwd;

	new_pwd = get_new_pwd(data, data->pwd, my_env, my_garbage);
	old_pwd = ft_strdup(data->pwd, my_garbage);
	if (new_pwd == NULL)
		return ;
	if (chdir(new_pwd) == -1)
	{
		handle_failure(data, my_env, my_garbage);
		return ;
	}
	data->cmd[0] = ft_strjoin("modify OLDPWD=", old_pwd, my_garbage);
	update_pwd(data, my_garbage);
	data->cmd[0] = ft_strjoin(
			data->cmd[0],
			ft_strjoin(" PWD=", data->pwd, my_garbage),
			my_garbage);
	data->cmd = ft_split(data->cmd[0], ' ', my_garbage);
	ft_export(data, my_env, my_garbage);
	set_exit_status(EXIT_SUCCESS);
}
