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

t_2_exec	*parsing(char *line)
{
	char		*tmp;
	t_garbage	*garbage;
	t_2_exec	*lst;

	tmp = line;
	garbage = NULL;
	line = ft_strtrim(line, " \t", &garbage);
	free(tmp);
	if (ft_check_syntax_error(line) == -1)
		return (NULL);
	lst = ft_analyse(line, &garbage);
	int i = 0;
	t_file *tmp1  = lst->files;
	while (tmp1)
	{
		printf("file %s type %d\n", tmp1->name, tmp1->type);
		tmp1 = tmp1->next;
	}
	printf("commands: \n");
	while (lst)
	{
		while (lst->cmd[i])
			printf("%s\n", lst->cmd[i++]);
		i = 0;
		lst = lst->next;
	}
	clear_garbage(&garbage);
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_2_exec	*lst;

	lst = NULL;
	while (1)
	{
		line = readline("minishell $");
		if (line && line[0])
		{
			add_history(line);
			lst = parsing(line);
		}
	}
	return (0);
}
