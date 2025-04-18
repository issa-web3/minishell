/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:55:48 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 16:53:02 by ioulkhir         ###   ########.fr       */
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
		if (*str != '-' || strs[i][1] != 'n')
			break ;
		while (*(++str) == 'n')
			;
		if (*str)
			break ;
		i++;
	}
	return (--i);
}

void	ft_echo(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	int	i;
	int	end;

	(void)my_env;
	(void)my_garbage;
	if (data->cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	end = has_dash_n(data->cmd);
	i = end;
	while (data->cmd[++i])
	{
		write(1, data->cmd[i], ft_strlen(data->cmd[i]));
		write(1, " ", data->cmd[i + 1] != NULL);
	}
	write(1, "\n", !end);
}
