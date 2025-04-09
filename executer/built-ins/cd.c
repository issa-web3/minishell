/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/09 13:56:24 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_new_pwd(t_2_exec *data, char *pwd, t_env **my_env,
		t_garbage **gc)
{
	char	*new_pwd;
	t_env	*env_tmp;

	set_exit_status(EXIT_FAILURE);
	if (data->cmd[1] == NULL)
	{
		env_tmp = ft_getenv("HOME", my_env);
		if (env_tmp == NULL)
			return (write(2, "cd: HOME not set\n", 17), NULL);
		new_pwd = env_tmp->value;
	}
	else if (pwd == NULL && !ft_strcmp(data->cmd[1], ".."))
	{
		write(2, "cd: error retrieving current directory", 38);
		write(2, ": getcwd: cannot access parent directo", 38);
		write(2, "ries: No such file or directory/n", 32);
	}
	else if (data->cmd[2])
		return (write(2, "cd: too many arguments\n", 23), NULL);
	else if (data->cmd[1][0] == '/')
		new_pwd = data->cmd[1];
	else
		new_pwd = ft_strjoin(ft_strjoin(pwd, "/", gc), data->cmd[1], gc);
	set_exit_status(EXIT_SUCCESS);
	return (new_pwd);
}

void	ft_cd(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	char	pwd[1024];
	char	*pwd_ptr;
	char	*new_pwd;

	pwd_ptr = getcwd(pwd, 1024);
	new_pwd = get_new_pwd(data, pwd_ptr, my_env, my_garbage);
	if (new_pwd == NULL)
		return ;
	if (chdir(new_pwd) == -1)
	{
		set_exit_status(NO_SUCH_FILE_OR_DIR);
		perror(ft_strjoin("cd: ", new_pwd, my_garbage));
		return ;
	}
	data->cmd[0] = ft_strjoin(
			ft_strjoin("export OLDPWD=", pwd, my_garbage),
			ft_strjoin(" PWD=", new_pwd, my_garbage)
		, my_garbage);
	data->cmd = ft_split(data->cmd[0], ' ', my_garbage);
	ft_export(data, my_env, my_garbage);
}
