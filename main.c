/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/22 17:27:23 by test             ###   ########.fr       */
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

char	*ft_readline(void)
{
	char	*line;

	line = readline("rich-3.14 $~ ");
	if (!line)
	{
		set_exit_status(0);
		exit(0);
	}
	return (line);
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
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = ft_readline();
		if (line && *line)
		{
			my_garbage = malloc(sizeof(t_garbage));
			if (my_garbage == NULL)
				break ;
			my_garbage->my_env = &my_env;
			my_garbage->data = NULL;
			my_garbage->ptr = NULL;
			my_garbage->next = NULL;
			data = parsing(line, &my_env, &my_garbage);
			if (data)
			{
				my_garbage->data = data;
				data->default_path = &default_path;
				set_exit_status(SUCCESS);
				execute(data, &my_env, &my_garbage);
			}
			add_history(line);
		}
		clear_garbage(&my_garbage);
	}
	clear_env(&my_env);
}
