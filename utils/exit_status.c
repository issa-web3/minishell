/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:44:15 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/08 13:43:48 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	manage_exit_status(int new)
{
	static int	exit_status_val;

	if (new != -1)
		exit_status_val = new;
	return (exit_status_val);
}

int	get_exit_status(void)
{
	return (manage_exit_status(-1));
}

void	set_exit_status(int new)
{
	manage_exit_status(new);
}
