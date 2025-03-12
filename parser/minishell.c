/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:46 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/12 01:13:52 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_2_exec	*parsing(char *line, char **envp)
{
	char		*tmp;
	t_garbage	*garbage;
	t_2_exec	*lst;
	t_env		*envl;

	garbage = NULL;
	envl = copy_env(envp, &garbage);
	tmp = line;
	line = ft_strtrim(line, " \t", &garbage);
	free(tmp);
	if (ft_check_syntax_error(line) == -1)
		return (NULL);
	lst = ft_analyse(line, envl, &garbage);
	int i = 0;
	int c = 0;
	while (lst)
	{
		printf("commands[%d]: \n", c);
		i = 0;
		while (lst->cmd && lst->cmd[i])
			printf("[%s]\n", lst->cmd[i++]);
		t_file *tmp1  = lst->files;
		while (tmp1)
		{
			printf("file [%s] type [%d]\n", tmp1->name, tmp1->type);
			tmp1 = tmp1->next;
		}
		c++;
		lst = lst->next;
	}
	clear_garbage(&garbage);

	return (NULL);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char		*line;
// 	t_2_exec	*lst;
// 	lst = NULL;
// 	// signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		line = readline("minishell ~");
// 		if (line && line[0])
// 		{
// 			add_history(line);
// 			lst = parsing(line, envp);
// 		}
// 	}
// 	return (0);
// }
