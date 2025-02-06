/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:46:31 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/06 16:21:11 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	count_words(const char *str, char c)
{
	int	count;
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && check_sep(str[i], c) == 1)
			i++;
		if (str[i] && check_sep(str[i], c) == 0)
		{
			count++;
			while (str[i] && check_sep(str[i], c) == 0)
				i++;
		}
	}
	return (count);
}
