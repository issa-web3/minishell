/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/16 13:33:33 by ioulkhir         ###   ########.fr       */
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
	char		*default_path;

	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (1);
	init(&my_garbage, &my_env, env, &default_path);
	while (1)
	{
		line = ft_readline(&my_env);
		init_garbage(&my_garbage, &my_env, NULL);
		data = parsing(line, &my_env, &my_garbage);
		if (data)
		{
			data->default_path = &default_path;
			my_garbage->data = data;
			g_signals = SIGINT;
			add_history(line);
			execute(data, &my_env, &my_garbage);
			g_signals = 0;
		}
		free(line);
		clear_garbage(&my_garbage);
	}
	clear_env(&my_env);
}
