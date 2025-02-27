/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-21 14:54:18 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-21 14:54:18 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_back_t2exec(t_2_exec **lst, t_2_exec *new)
{
	t_2_exec	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

void	ft_lstadd_back_t_file(t_file **lst, t_file *new)
{
	t_file	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

int	can_i_expand(char *str)
{
	if (ft_strchr(str, '$'))
		return (1);
	return (0);
}

t_expand	*ft_create_expand_node(char *s, t_garbage **garbage)
{
	t_expand	*node;

	node = ft_malloc(sizeof(t_expand), garbage);
	node->value = s;
	node->next = NULL;
}

void	ft_lstadd_back_t_expand(t_expand **lst, t_expand *new)
{
	t_expand	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
}
