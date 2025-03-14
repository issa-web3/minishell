/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:13:26 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/14 10:13:06 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_value_env(char *str, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*extract_var_name(char *str,
	int *index, t_garbage **garbage)
{
	char	*var_name;
	int		len;
	int		start;

	len = 0;
	start = *index;
	while (str[*index] && is_valid_var(str[*index]))
		len += ((*index)++, 1);
	var_name = ft_strldup(&str[start], len, garbage);
	return (var_name);
}

static char	*expand_variable(char *str, int *index,
	t_env *env, t_garbage **garbage)
{
	char	*res;
	char	*var_name;

	(*index)++;
	if (str[*index] == '?')
	{
		(*index)++;
		return (ft_strdup("exit status here\n", garbage));
	}
	if (str[*index] == '\0' || !is_valid_var(str[*index]))
		return (ft_strdup("$", garbage));
	var_name = extract_var_name(str, index, garbage);
	res = ft_get_value_env(var_name, env);
	return (res);
}

static char	*concatenate(char *res, char *str, int len, t_garbage **g)
{
	return (ft_strjoin(res, ft_strldup(str, len, g), g));
}

char	*ft_replace_dollar(char *str, t_env *env, t_garbage **garbage)
{
	char	*res;
	int		index;
	int		start;

	1 && (index = 0, res = NULL);
	while (str[index])
	{
		start = index;
		while (str[index])
		{
			if (str[index] == '$')
			{
				if (start != index)
					res = concatenate(res, &str[start], index - start, garbage);
				break ;
			}
			index++;
			if (str[index] == '\0')
				res = concatenate(res, &str[start], index - start, garbage);
		}
		if (str[index] && str[index] == '$')
			res = ft_strjoin(res,
					expand_variable(str, &index, env, garbage), garbage);
	}
	return (res);
}
