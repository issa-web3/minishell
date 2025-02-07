/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:30:29 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/07 11:23:07 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	free_split(char **split, int i)
{
	int	j;

	j = i;
	if (split == NULL)
		return ;
	while (split[j])
		free(split[j++]);
	free(split);
}

static char	**get_paths(void)
{
	char	**paths;
	int		i;
	char	cwd[1024];

	i = 0;
	getcwd(cwd, sizeof(cwd));
	paths = ft_split(getenv("PATH"), ':', NULL);
	return (paths);
}

char	*get_path(char *cmd)
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
	paths = get_paths();
	if (paths == NULL)
		return (free(cmd), NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i++], "/"), cmd);
		if (access((const char *)path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	return (free_split(paths, i), free(cmd), path);
}
