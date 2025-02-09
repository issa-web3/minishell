/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:04:32 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 14:20:05 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

int	ft_pipe(int *arr)
{
	int	result;

	result = pipe(arr);
	if (result != -1)
		return (result);
	perror("pipe");
	return (-1);
}
