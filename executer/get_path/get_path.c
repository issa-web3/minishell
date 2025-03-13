/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:30:29 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/13 10:39:38 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static char	**get_paths(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	char	**paths;
	int		i;
	char	cwd[1024];
	t_env	*path_var;

	i = 0;
	paths = NULL;
	getcwd(cwd, sizeof(cwd));
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
	path = NULL;
	if (access((const char *)data->cmd[0], X_OK) == 0)
		return (data->cmd[0]);
	if (!ft_strncmp(data->cmd[0], "./", 2) || data->cmd[0][0] == '/')
		return (NULL);
	paths = get_paths(data, my_env, my_garbage);
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(
				ft_strjoin(paths[i++], "/", my_garbage),
				data->cmd[0], my_garbage);
		if (access((const char *)path, X_OK) == 0)
			break ;
		path = NULL;
	}
	return (path);
}
