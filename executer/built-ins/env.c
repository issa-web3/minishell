/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/16 12:06:04 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage, char is_child)
{
	t_env	*curr;

	curr = *my_env;
	(void)data;
	(void)my_garbage;
	(void)is_child;
	while (curr)
	{
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}
