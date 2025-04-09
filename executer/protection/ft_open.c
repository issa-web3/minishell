/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:04:32 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/09 10:38:49 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

int	ft_open(char *filename, int mode)
{
	int	result;

	result = open(filename, mode, 0644);
	if (result != -1)
		return (set_exit_status(NO_SUCH_FILE_OR_DIR), result);
	perror(filename);
	return (-1);
}
