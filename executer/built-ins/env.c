/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:55:55 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/22 07:07:18 by ioulkhir         ###   ########.fr       */
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
	while (data->cmd[1] == NULL && curr && curr->value)
	{
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
	set_exit_status(EXIT_SUCCESS);
	if (data->cmd[1])
	{
		write(2, "env: too many arguments\n", 24);
		set_exit_status(EXIT_FAILURE);
	}
}
