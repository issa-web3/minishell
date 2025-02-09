/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:04:32 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/09 14:19:35 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

int	ft_dup2(int a, int b)
{
	int	result;

	result = dup2(a, b);
	if (result != -1)
		return (result);
	perror("dup2");
	return (-1);
}
