/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:55:55 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/05 13:09:38 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_2_exec	*ft_lstnew(t_2_exec data)
{
	t_2_exec	*new_node;

	new_node = (t_2_exec *)malloc(sizeof(t_2_exec));
	if (!new_node)
		return (new_node);
	new_node->cmd = data.cmd;
	new_node->file = data.file;
	new_node->next = NULL;
	return (new_node);
}
