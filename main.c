/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025/02/08 10:00:04 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char		*line;
	t_2_exec	*data;
	char		cwd[1024];
	t_env		*my_env;

	// make copy of env
	my_env = copy_env(env);
	while (1)
	{
		getcwd(cwd, sizeof(cwd)); // protect ft_strrchr
		line = readline(
				ft_strjoin(ft_strdup("rich-3.14 ["),
					ft_strjoin(ft_strdup(ft_strrchr(cwd, '/')), "] $ ")));
		data = parser(ac, av, my_env, line);
		execute(data, my_env);
		add_history(line);
	}
}
