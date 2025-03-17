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

t_2_exec	*parsing(char *line, t_env **envl, t_garbage **garbage)
{
	t_2_exec	*lst;

	line = ft_strdup(line, garbage);
	line = ft_strtrim(line, " \t", garbage);
	if (ft_check_syntax_error(line) == -1)
	{
		set_exit_status(2);
		return (NULL);
	}
	lst = ft_analyse(line, *envl, garbage);
	return (lst);
}
