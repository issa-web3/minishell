/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/07 13:57:29 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char **cmd, char **env)
{
	char	buffer[1024];

	if (cmd[1] == NULL)
	{
		if (chdir("/") == -1)
			perror("cd");
	}
	else
	{
		getcwd(buffer, 1024);
		if (chdir(ft_strjoin(ft_strjoin(ft_strdup(buffer), "/"), cmd[1])) == -1)
			perror("cd");
	}
}
