/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:30:29 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/23 12:06:39 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	is_command_not_found(t_2_exec *data, char *path)
{
	if (path == NULL)
	{
		set_exit_status(COMMAND_NOT_FOUND);
		write(2, data->cmd[0], ft_strlen(data->cmd[0]));
		write(2, ": command not found\n", 20);
	}
}

char	*check_dir(t_2_exec *data)
{
	char		*cmd;
	struct stat	file_stat;

	cmd = data->cmd[0];
	if (!ft_strcmp(cmd, "..") || !ft_strcmp(cmd, ".") || cmd[0] == '\0')
		return (is_command_not_found(data, NULL), NULL);
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

char	*check_access_directly(char *cmd)
{
	if (access((const char *)cmd, F_OK) == -1)
		return (set_exit_status(COMMAND_NOT_FOUND), perror(cmd), NULL);
	else if (access((const char *)cmd, X_OK) == -1)
		return (set_exit_status(INVALID_EXIT_STATUS), perror(cmd), NULL);
	return (cmd);
}

char	*check_the_path_env(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	char	*path;
	char	*cmd;
	char	**paths;
	int		i;

	i = 0;
	cmd = data->cmd[0];
	paths = get_paths(data, my_env, my_garbage);
	path = NULL;
	while (paths && paths[i])
	{
		path = ft_strjoin(
				ft_strjoin(paths[i++], "/", my_garbage),
				cmd, my_garbage);
		if (access((const char *)path, X_OK) == 0)
			break ;
		path = NULL;
	}
	return (path);
}
