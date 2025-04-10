/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-19 15:19:21 by khoukouj          #+#    #+#             */
/*   Updated: 2025-03-19 15:19:21 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_expand_heredoc(char *del)
{
	int	i;

	i = 0;
	if (!del)
		return (0);
	while (del[i])
	{
		if (is_quote(del[i]))
			return (0);
		i++;
	}
	return (1);
}
t_file	*new_file_node(char *name, t_garbage **g, char *buff)
{
	t_file	*node;
	int		fd;

	fd = open(name, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
		return (NULL);
	write (fd, buff, ft_strlen(buff));
	node = ft_malloc(sizeof(t_file), g);
	node->name = name;
	node->type = IN_FILE;
	node->next = NULL;
	return (node);
}

char	*generate_file_name(t_garbage	**g)
{
	static int	num;
	char		*name;
	char		*res;
	char		*tmp_path;

	res = NULL;
	tmp_path = ft_strdup("/tmp/heredoc_", g);
	num = (num * 121) % 232332;
	name = ft_itoa(num, g);
	res = ft_strjoin(tmp_path, name, g);
	return (res);
}
