/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:30:29 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/12 14:37:25 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static char	**get_paths(t_env **my_env, t_garbage **my_garbage)
{
	char	**paths;
	int		i;
	char	cwd[1024];
	t_env	*path_var;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	path_var = ft_getenv("PATH", my_env);
	if (path_var == NULL)
		return (NULL);
	paths = ft_split(path_var->value, ':', my_garbage);
	return (paths);
}

char	*get_path(char *cmd, t_env **my_env, t_garbage **my_garbage)
{
	char	**paths;
	char	*path;
	int		i;

	if (cmd == NULL)
		return (NULL);
	path = NULL;
	if (access((const char *)cmd, X_OK) == 0)
		return (cmd);
	if (!ft_strncmp(cmd, "./", 2) || cmd[0] == '/')
		return (NULL);
	paths = get_paths(my_env, my_garbage);
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
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
