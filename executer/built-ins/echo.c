/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/07 09:52:59 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **cmd, char **env)
{
	int	i;
	int	end;

	if (cmd[1] == NULL)
		return (write(1, "\n", 1), 0);
	i = 0;
	end = ft_strcmp(cmd[1], "-n");
	!end && i++;
	while (cmd[++i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		cmd[i + 1] != NULL && write(1, " ", 1);
	}
	(end) && (write(1, "\n", 1));
}


// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options