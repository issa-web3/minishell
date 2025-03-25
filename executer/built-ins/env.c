/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/25 00:01:28 by test             ###   ########.fr       */
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
	while (curr && (curr->value || 1))
	{
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}
