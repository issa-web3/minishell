/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/08 11:25:21 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(char **cmd, t_env *my_env)
{
	t_env	*to_rm;
	int		i;

	i = 1;
	while (cmd[i])
	{
		to_rm = ft_getenv(cmd[i], my_env);
		del_env_var(to_rm, my_env);
		i++;
	}
}
