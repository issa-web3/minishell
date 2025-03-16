/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/16 11:31:02 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	has_dash_n(char **strs)
{
	char	*str;
	int		i;

	i = 1;
	while (strs[i])
	{
		str = strs[i];
		if (*str != '-')
			break ;
		while (*(++str) == 'n')
			;
		if (*str)
			break ;
		i++;
	}
	return (--i);
}

void	ft_echo(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child)
{
	int	i;
	int	end;

	(void)my_env;
	(void)my_garbage;
	(void)is_child;
	if (data->cmd[1] == NULL)
		(write(1, "\n", 1), exit(EXIT_SUCCESS));
	end = has_dash_n(data->cmd);
	i = end;
	while (data->cmd[++i])
	{
		write(1, data->cmd[i], ft_strlen(data->cmd[i]));
		write(1, " ", data->cmd[i + 1] != NULL);
	}
	write(1, "\n", !end);
	exit(EXIT_SUCCESS);
}
