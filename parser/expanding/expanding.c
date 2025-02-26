/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-25 03:27:22 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-25 03:27:22 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_between_quotes(char *str, int *i, int quote, t_garbage **garbage)
{
	char	*res;
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && is_quote(str[*i]) != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
	res = ft_strldup(&str[start], *i - start, garbage);
	return (res);
}

static void	create_plain_seg(char *str, char **res, int *i, t_garbage **garbage)
{
	int	start;

	start = *i;
	while (str[*i] && !is_quote(str[*i]))
		(*i)++;
	if (start != *i)
		*res = ft_strldup(&str[start], *i - start, garbage);
}
