/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/07 23:57:25 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char **cmd, char **env)
{
	char	buffer[1024];

	// need general code here bro
	if (cmd[1] == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd");
	}
	else if (cmd[1][0] == '/')
	{
		getcwd(buffer, 1024);
		if (chdir(cmd[1]) == -1)
			perror("cd");
	}
	else if (cmd[1][0] == '~')
	{
		getcwd(buffer, 1024);
		if (chdir(ft_strjoin(ft_strdup(getenv("HOME")), cmd[1] + 1)) == -1)
			perror("cd");
	}
	else if (cmd[1][0] == '-')
	{
		if (cmd[1][1])
		{
			write(2, "invalid option\n", 15);
			return ;
		}
		write(1, getenv("OLDPWD"), ft_strlen(getenv("OLDPWD"))); // protection
		getcwd(buffer, 1024);
		if (chdir(getenv("OLDPWD")) == -1)
			perror("cd");
	}
	else
	{
		getcwd(buffer, 1024);
		if (chdir(ft_strjoin(ft_strjoin(ft_strdup(buffer), "/"), cmd[1])) == -1)
			perror("cd");
	}
	// update OLDPWD
	// get OLDPWD
}
