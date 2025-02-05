/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-05 13:00:46 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-05 13:00:46 by khoukouj         ###   ########.1337.ma  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_from_input(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			return ;
		if (!line[0])
		{
			free(line);
			continue;
		}
		if (line[0])
			add_history(line);
		parse_line(line);
	}
}

// int main(int ac, char **av, char **envp)
// {

// }