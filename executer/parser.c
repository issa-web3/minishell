/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:11:12 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/11 14:24:29 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	strs_len(char **arr)
{
	size_t	len;

	len = 0;
	if (arr == NULL)
		return (len);
	while (arr[len++]);
	return (len);
}

t_2_exec	*parser(int ac, char **av, t_env *my_env, t_garbage **my_garbage, char *line)
{
	t_2_exec	*head;
	t_2_exec	data;
	char		**cmds;
	int			out;
	int			i;
	int			j;

	if (line == NULL)
		return (NULL);
	cmds = ft_split(line, '|', my_garbage);
	i = 0;
	out = 0;
	head = NULL;
	while (cmds[i])
	{
		data.cmd = ft_split(cmds[i++], ' ', my_garbage);
		j = 0;
		data.infile = NULL;
		data.outfiles = ft_malloc(strs_len(data.cmd) * sizeof(char *), my_garbage);
		data.appends = ft_malloc(strs_len(data.cmd) * sizeof(char), my_garbage);
		while (data.cmd && data.cmd[j])
		{
			if (ft_strcmp(data.cmd[j], "<") == 0)
				(data.infile = data.cmd[j + 1], data.cmd[j] = NULL);
			else if (ft_strcmp(data.cmd[j], "<<") == 0)
				(data.infile = data.cmd[j + 1], data.cmd[j] = NULL);
			else if (ft_strcmp(data.cmd[j], ">") == 0)
				(data.outfiles[out] = data.cmd[j + 1], data.cmd[j] = NULL, data.appends[out++] = 0);
			else if (ft_strcmp(data.cmd[j], ">>") == 0)
				(data.outfiles[out] = data.cmd[j + 1], data.cmd[j] = NULL, data.appends[out++] = 1);
			j++;
		}
		data.outfiles[out] = NULL;
		ft_lstadd_back(&head, ft_lstnew(data, my_garbage), my_garbage);
	}
	return head;
}
