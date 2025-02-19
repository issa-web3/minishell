/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 15:14:18 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-17 15:14:18 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr(char *s, int start, size_t len, t_garbage **to_free)
{
	char	*sub_str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub_str = ft_malloc(len + 1, to_free);
	if (!sub_str)
		return (NULL);
	while (i < len)
	{
		sub_str[i] = s[i + start];
		i++;
	}
	sub_str[i] = 0;
	return (sub_str);
}

char	*ft_strtrim(char *str, char *set, t_garbage **to_free)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!str || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	while (end > start && ft_strchr(set, str[end - 1]))
		end--;
	res = ft_substr(str, (int)start, end - start, to_free);
	return (res);
}

void	ft_skip_quotes(char *str, int *i)
{
	char	q;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		q = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != q)
			(*i)++;
		if (str[*i] == q)
			(*i)++;
	}
}
char	*ft_strldup(char *str, size_t len, t_garbage **garbage)
{
	char	*res;
	int		i;

	i = 0;
	if (ft_strlen(str) < len)
		return (NULL);
	res = ft_malloc(len + 1, garbage);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[len] = '\0';
	return (res);
}

void	ft_append_to_lst(t_token **lst, t_token *node)
{
	t_token	*last;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		(*lst)->next = NULL;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = node;
	node->next = NULL;
}
