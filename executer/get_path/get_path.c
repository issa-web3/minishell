/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:30:29 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/25 02:40:39 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static void	command_not_found(t_2_exec *data, char *path)
{
	if (path == NULL)
	{
		set_exit_status(COMMAND_NOT_FOUND);
		write(2, data->cmd[0], ft_strlen(data->cmd[0]));
		write(2, ": command not found\n", 20);
	}
}

static void	no_such_file_or_dir(t_2_exec *data, char *path)
{
	char	*cmd;

	cmd = data->cmd[0];
	if (
		(path == NULL && cmd[0] == '/')
		|| (path && ft_strcmp(cmd, path) && cmd[0] == '/')
		|| (path && ft_strcmp(cmd, path) && !ft_strncmp(cmd, "./", 2))
		|| (path == NULL && !ft_strncmp(cmd, "./", 2))
	)
	{
		set_exit_status(COMMAND_NOT_FOUND);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
	}
}

static char	**get_paths(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	char	**paths;
	t_env	*path_var;

	paths = NULL;
	path_var = ft_getenv("PATH", my_env);
	if (path_var == NULL)
		paths = ft_split(*data->default_path, ':', my_garbage);
	else
		paths = ft_split(path_var->value, ':', my_garbage);
	return (paths);
}

char	*get_path(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	char	**paths;
	char	*path;
	int		i;

	if (data->cmd[0] == NULL)
		return (NULL);
	i = 0;
	path = NULL;
	paths = get_paths(data, my_env, my_garbage);
	if ((!ft_strncmp(data->cmd[0], "./", 2) || data->cmd[0][0] == '/')
		&& access((const char *)data->cmd[0], X_OK) == 0)
		path = data->cmd[0];
	while (!path && paths && paths[i])
	{
		path = ft_strjoin(
				ft_strjoin(paths[i++], "/", my_garbage),
				data->cmd[0], my_garbage);
		if (access((const char *)path, X_OK) == 0)
			break ;
		path = NULL;
	}
	no_such_file_or_dir(data, path);
	command_not_found(data, path);
	return (path);
}
