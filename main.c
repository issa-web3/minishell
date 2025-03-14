/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/13 11:19:28 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_default_path(char *str, t_env **my_env)
{
	char	*default_path;

	default_path = malloc(ft_strlen(str));
	if (default_path == NULL)
		(clear_env(my_env), perror("malloc"), exit(EXIT_FAILURE));
	ft_strlcpy(default_path, str, ft_strlen(str));
	return (default_path);
}

static void	init(t_garbage **my_garbage, t_env **my_env,
		char **env, char **default_path)
{
	*my_garbage = NULL;
	*my_env = copy_env(env);
	*default_path = get_default_path(
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
			my_env
			);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_2_exec	*data;
	t_env		*my_env;
	t_garbage	*my_garbage;
	char		*default_path;

	(void)ac;
	(void)av;
	init(&my_garbage, &my_env, env, &default_path);
	while (1)
	{
		line = readline("rich-3.14 $~ ");
		if (line && *line)
		{
			data = parsing(line, &my_env, &my_garbage);
			if (data)
			{
				data->default_path = &default_path;
				execute(data, &my_env, &my_garbage);
			}
			add_history(line);
		}
		clear_garbage(&my_garbage);
	}
	clear_env(&my_env);
}
