/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-19 15:19:21 by khoukouj          #+#    #+#             */
/*   Updated: 2025-03-19 15:19:21 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_expand_heredoc(char *del)
{
	int	i;

	i = 0;
	if (!del)
		return (0);
	while (del[i])
	{
		if (is_quote(del[i]))
			return (0);
		i++;
	}
	return (1);
}
