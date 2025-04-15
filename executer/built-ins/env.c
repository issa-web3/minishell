/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:55:55 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/15 10:55:56 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	t_env	*curr;

	curr = *my_env;
	(void)data;
	(void)my_garbage;
	while (curr && curr->value)
	{
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}
