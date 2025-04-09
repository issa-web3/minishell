/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:30:29 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/09 11:05:30 by ioulkhir         ###   ########.fr       */
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

static char	*check_dir(t_2_exec *data)
{
	char		*cmd;
	struct stat	file_stat;

	cmd = data->cmd[0];
	if (!ft_strcmp(cmd, "..") || cmd[0] == '\0')
		return (command_not_found(data, NULL), NULL);
	if (stat(cmd, &file_stat) == 0
		&& S_ISDIR(file_stat.st_mode) && ft_strchr(cmd, '/'))
	{
		set_exit_status(INVALID_EXIT_STATUS);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 17);
		return (NULL);
	}
	return (cmd);
}

char	*get_path(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	char	**paths;
	char	*cmd;
	char	*path;
	int		i;

	cmd = check_dir(data);
	if (cmd == NULL)
		return (NULL);
	i = 0;
	path = NULL;
	paths = get_paths(data, my_env, my_garbage);
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
	{
		if (access((const char *)cmd, F_OK) == -1)
			return (set_exit_status(COMMAND_NOT_FOUND), perror(cmd), NULL);
		else if (access((const char *)cmd, X_OK) == -1)
			return (set_exit_status(INVALID_EXIT_STATUS), perror(cmd), NULL);
		return (cmd);
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
	command_not_found(data, path);
	return (path);
}
