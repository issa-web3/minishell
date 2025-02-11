/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:55:55 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/11 10:22:52 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_2_exec	*ft_lstnew(t_2_exec data, t_garbage **my_garbage)
{
	t_2_exec	*new_node;

	new_node = (t_2_exec *)ft_malloc(sizeof(t_2_exec), my_garbage);
	new_node->cmd = data.cmd;
	new_node->infile = data.infile;
	new_node->outfile = data.outfile;
	new_node->next = NULL;
	return (new_node);
}
