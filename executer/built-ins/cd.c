/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/16 12:05:55 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_new_pwd(t_2_exec *data, char *pwd, t_env **my_env,
		t_garbage **gc)
{
	char	*new_pwd;
	t_env	*home;

	if (data->cmd[1] == NULL)
	{
		home = ft_getenv("HOME", my_env);
		if (home == NULL)
			return (write(2, "cd: HOME not set\n", 17), NULL);
		new_pwd = home->value;
	}
	else if (data->cmd[1][0] == '/')
		new_pwd = data->cmd[1];
	else
		new_pwd = ft_strjoin(ft_strjoin(pwd, "/", gc), data->cmd[1], gc);
	return (new_pwd);
}

void	ft_cd(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage, char is_child)
{
	char	pwd[1024];
	char	*new_pwd;

	(void)is_child;
	getcwd(pwd, 1024);
	new_pwd = get_new_pwd(data, pwd, my_env, my_garbage);
	if (new_pwd == NULL)
		return ;
	if (chdir(new_pwd) == -1)
		perror("cd");
}
