/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/26 03:23:05 by test             ###   ########.fr       */
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
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	*my_garbage = NULL;
	*my_env = copy_env(env);
	*default_path = get_default_path(
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
			my_env
			);
}

char	*ft_readline(void)
{
	char	*line;

	line = readline("rich-3.14 $~ ");
	if (!line)
	{
		set_exit_status(SUCCESS);
		exit(SUCCESS);
	}
	return (line);
}

void	init_garbage(t_garbage **my_garbage, t_env **my_env, t_2_exec *data)
{
	(*my_garbage) = malloc(sizeof(t_garbage));
	if ((*my_garbage) == NULL)
		(clear_env(my_env), perror("malloc"), exit(EXIT_FAILURE));
	(*my_garbage)->my_env = my_env;
	(*my_garbage)->data = data;
	(*my_garbage)->ptr = NULL;
	(*my_garbage)->next = NULL;
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
		line = ft_readline();
		init_garbage(&my_garbage, &my_env, NULL);
		data = parsing(line, &my_env, &my_garbage);
		if (data)
		{
			data->default_path = &default_path;
			init_garbage(&my_garbage, &my_env, data);
			add_history(line);
			free(line);
			execute(data, &my_env, &my_garbage);
		}
		clear_garbage(&my_garbage);
	}
	clear_env(&my_env);
}
