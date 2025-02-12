/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/12 08:29:18 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_clear(char **cmd, t_env *my_env, t_garbage **my_garbage)
{
	(void)cmd;
	(void)my_garbage;
	(void)my_env;
	system("clear");
}
