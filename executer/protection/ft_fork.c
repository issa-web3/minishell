/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:04:32 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 14:07:09 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

pid_t	ft_fork(void)
{
	pid_t	result;

	result = fork();
	if (result != -1)
		return (result);
	perror("fork");
	return (-1);
}
