/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-06 10:56:41 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-06 10:56:41 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trimed_len(char *line)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = strlen_pars(line) - 1;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (i == strlen_pars(line))
		return (0);
	while (j > 0 && is_whitespace(line[j]))
		j--;
	len = j - i + 1;
	return (len);
}

char	*trim_line(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*trimed;

	len = trim_line(line);
	if (len == 0)
		return (NULL);
	i = 0;
	j = 0;
	trimed = NULL;
	trimed = malloc(len + 1);
	if (!trimed)
		return (NULL);
	while (line[i] && is_whitespace(line[i]))
		i++;
	while (line[i] && j < len)
	{
		trimed[i] = line[i];
		i++;
		j++;
	}
	trimed[j] = '\0';
	return (trimed);
}
