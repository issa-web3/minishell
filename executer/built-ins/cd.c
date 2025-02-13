/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/13 14:24:20 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_new_pwd(char **cmd, t_env *old_pwd, char *pwd, t_env **my_env, t_garbage **my_garbage)
{
	char	*new_pwd;
	t_env	*home;

	if (cmd[1] == NULL)
	{
		home = ft_getenv("HOME", my_env);
		if (home == NULL)
			return (write(2, "cd: HOME not set\n", 17), NULL);
		new_pwd = home->value;
	}
	else if (cmd[1][0] == '/')
		new_pwd = cmd[1];
	else if (cmd[1][0] == '~')
		new_pwd = ft_strjoin(ft_strdup(ft_getenv("HOME", my_env)->value, my_garbage), cmd[1] + 1, my_garbage);
	else if (cmd[1][0] == '-')
	{
		if (cmd[1][1])
			return (write(2, "invalid option\n", 15), NULL);
		if (old_pwd == NULL)
			return (write(2, "cd: OLDPWD not set\n", 19), NULL);
		new_pwd = old_pwd->value;
	}
	else
		new_pwd = ft_strjoin(ft_strjoin(pwd, "/", my_garbage), cmd[1], my_garbage); // protection
	return (new_pwd);
}

void	ft_cd(char **cmd, t_env **my_env, t_garbage **my_garbage)
{
	char	pwd[1024];
	char	*pwd_ptr;
	t_env	*old_pwd;
	char	*new_pwd;
	char	*cmd_export[2];

	getcwd(pwd, 1024);
	// pwd_ptr = ft_strdup(pwd, my_garbage);
	old_pwd = ft_getenv("OLDPWD", my_env);
	new_pwd = get_new_pwd(cmd, old_pwd, pwd, my_env, my_garbage);
	if (new_pwd == NULL)
		return ;
	if (chdir(new_pwd) == -1)
		perror("cd");
	else
	{
		cmd_export[1] = ft_strjoin("OLDPWD=", pwd, my_garbage);
		ft_export(cmd_export, my_env, my_garbage);
		if (cmd[1] && cmd[1][0] == '-')
		{
			write(1, old_pwd->value, ft_strlen(old_pwd->value));
			write(1, "\n", 1);
		}
	}
}
