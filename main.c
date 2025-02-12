/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025/02/12 08:27:31 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char		*line;
	t_2_exec	*data;
	char		cwd[1024];
	t_env		*my_env;
	t_garbage	*my_garbage;

	// make copy of env
	my_garbage = NULL;
	my_env = copy_env(env, &my_garbage);
	while (1)
	{
		getcwd(cwd, sizeof(cwd)); // protect ft_strrchr
		line = readline(
				ft_strjoin(ft_strdup("rich-3.14 [", &my_garbage),
					ft_strjoin(ft_strdup(ft_strrchr(cwd, '/'), &my_garbage), "] $ ", &my_garbage), &my_garbage));
		// if (line && 0)
		// 	append_garbage(&my_garbage, line);
		data = parser(ac, av, my_env, &my_garbage, line);
		execute(data, my_env, &my_garbage);
		add_history(line);
		// clear_garbage(&my_garbage);
	}
}
