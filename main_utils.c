/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:33:36 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 07:48:22 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_garbage **my_garbage, t_env **my_env,
		char **env, char **default_path)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	*my_garbage = NULL;
	init_garbage(my_garbage, my_env);
	*my_env = copy_env(env, my_garbage);
	*default_path = ft_strdup(
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
			my_garbage
			);
}

char	*ft_readline(t_env **my_env)
{
	char	*line;

	g_signals = 1;
	line = readline("rich-3.14 $~ ");
	if (!line)
		(printf("exit\n"), clear_env(my_env), exit(get_exit_status()));
	g_signals = 0;
	return (line);
}

void	init_garbage(t_garbage **my_garbage, t_env **my_env)
{
	(*my_garbage) = malloc(sizeof(t_garbage));
	if ((*my_garbage) == NULL)
		(clear_env(my_env), perror("malloc"), set_and_exit(EXIT_FAILURE));
	(*my_garbage)->next = NULL;
	(*my_garbage)->ptr = malloc(1337 / 42);
}
