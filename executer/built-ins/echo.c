/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/14 09:26:22 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	has_dash_n(char *str)
{
	if (*str != '-')
		return (0);
	while (*(++str) == 'n');
	return (*str == '\0');
}

void	ft_echo(char **cmd, t_env **my_env, t_garbage **my_garbage)
{
	int	i;
	int	end;

	(void)my_env;
	(void)my_garbage;
	if (cmd[1] == NULL)
		(write(1, "\n", 1), exit(EXIT_SUCCESS));
	i = 0;
	end = has_dash_n(cmd[1]);
	end && i++;
	while (cmd[++i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		cmd[i + 1] != NULL && write(1, " ", 1);
	}
	(!end) && (write(1, "\n", 1));
	exit(EXIT_SUCCESS);
}
