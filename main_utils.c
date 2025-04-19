/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:33:36 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/19 10:55:43 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_garbage **my_garbage, char **d_path,
		t_env **my_env, char **env)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (exit(EXIT_FAILURE));
	*d_path = "some king of string";
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	*my_garbage = NULL;
	*my_env = copy_env(env, my_garbage);
}

char	*ft_readline(t_garbage **my_garbage)
{
	char	*line;

	g_signals = 1;
	line = readline("rich-3.14 $~ ");
	if (!line)
		(printf("exit\n"), clear_all(my_garbage), exit(get_exit_status()));
	append_garbage(my_garbage, line);
	g_signals = 0;
	return (line);
}

void	init_garbage(t_garbage **my_garbage, t_env **my_env
		, char **d_path)
{
	(*my_garbage) = malloc(sizeof(t_garbage));
	if ((*my_garbage) == NULL)
		(clear_env(my_env), perror("malloc"), set_and_exit(EXIT_FAILURE));
	(*my_garbage)->next = NULL;
	(*my_garbage)->ptr = malloc(1337 / 42);
	if (*d_path)
		*d_path = ft_strdup(
				"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
				my_garbage
				);
}
