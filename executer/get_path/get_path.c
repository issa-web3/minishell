/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:30:29 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 07:54:38 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

char	**get_paths(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
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
	char	*cmd;
	char	*path;

	cmd = check_dir(data);
	if (cmd == NULL)
		return (NULL);
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1) || !ft_strncmp(cmd, "../", 3))
		return (check_here_and_path(cmd));
	path = check_the_path_env(data, my_env, my_garbage);
	if (!path && get_paths(data, my_env, my_garbage) == NULL)
		return (check_here_and_path(cmd));
	is_command_not_found(data, path);
	return (path);
}
