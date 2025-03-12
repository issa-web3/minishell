/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:46 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/12 13:47:35 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_2_exec	*parsing(char *line, t_env **envl)
{
	char		*tmp;
	t_garbage	*garbage;
	t_2_exec	*lst;

	garbage = NULL;
	line = ft_strdup(line, &garbage);
	tmp = line;
	line = ft_strtrim(line, " \t", &garbage);
	free(tmp);
	if (ft_check_syntax_error(line) == -1)
		return (NULL);
	lst = ft_analyse(line, *envl, &garbage);
	return (lst);
}
