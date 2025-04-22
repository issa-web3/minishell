/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:56:05 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 17:14:46 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_all(t_garbage **my_garbage)
{
	t_env			**my_env;

	if ((*my_garbage))
	{
		my_env = (*my_garbage)->my_env;
		clear_env(my_env);
	}
	clear_garbage(my_garbage);
}
