/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:30:29 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/08 10:23:14 by ioulkhir         ###   ########.fr       */
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

// plan:
	// 2- ./ --->  check HERE
	// 3- / --->   check /path/
	// 4- cmd ---> check PATH then check HERE
	// 1- check dir

char	*get_path(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	char	**paths;
	char	*cmd;
	char	*path;
	int		i;

	cmd = data->cmd[0];
	if (cmd == NULL)
		return (NULL);
	i = 0;
	path = NULL;
	paths = get_paths(data, my_env, my_garbage);
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
	{
		if (access((const char *)cmd, X_OK) == 0)
			return (cmd);
		no_such_file_or_dir(data, NULL);
		return (NULL);
	}
	while (!path && paths && paths[i])
	{
		path = ft_strjoin(
				ft_strjoin(paths[i++], "/", my_garbage),
				cmd, my_garbage);
		if (access((const char *)path, X_OK) == 0)
			break ;
		path = NULL;
	}
	no_such_file_or_dir(data, path);
	command_not_found(data, path);
	// is_a_dir(data, path);
	return (path);
}
