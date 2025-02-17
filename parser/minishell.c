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

int	parse_line(char *line)
{
	char	*tmp;
	t_token	*token;
	char	**split;

	(1) && (tmp = NULL, token = NULL, split = NULL);
	if (!check_unclosed_quotes(line))
	{
		printf("minishell: syntax error unclosed quotes\n");
		return (-1);
	}
	add_spaces(&line);
	1 && (tmp = line, line = trim_line(line));
	if (!line)
		return (-1);
	split = str_tokenize(line);
	if (!split)
		return (-1);
	if (tokenize(split, &token) == -1)
		return (-1);
	return (0);
}

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
			continue ;
		}
		if (line[0])
			add_history(line);
		if (parse_line(line) != -1)
			printf("\n");
	}
}



int	main(int ac, char **av, char **envp)
{
	read_from_input();
	return (0);
}
