/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:56:05 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/15 10:56:06 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_all(t_garbage **my_garbage)
{
	t_pipe			*pipes;
	t_env			**my_env;
	int				i;

	if ((*my_garbage))
	{
		my_env = (*my_garbage)->my_env;
		i = 3;
		while (i < 1024)
			close(i++);
		clear_env(my_env);
	}
	clear_garbage(my_garbage);
}
