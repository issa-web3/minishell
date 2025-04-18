/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/18 17:43:47 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signals = 0;

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_2_exec	*data;
	t_env		*my_env;
	t_garbage	*my_garbage;
	char		*d_path;

	(void)ac;
	(void)av;
	init(&my_garbage, &d_path, &my_env, env);
	while (1)
	{
		init_garbage(&my_garbage, &my_env, &d_path);
		my_garbage->my_env = &my_env;
		line = ft_readline(&my_garbage);
		if (*line)
			add_history(line);
		data = parsing(line, &my_env, &my_garbage);
		if (data)
		{
			data->d_path = &d_path;
			execute(data, &my_env, &my_garbage);
		}
		clear_garbage(&my_garbage);
	}
	clear_env(&my_env);
}
