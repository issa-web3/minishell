/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-27 13:13:26 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-27 13:13:26 by khoukouj         ###   ########ma        */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *extract_var_name(char *str, int *index, t_garbage **garbage)
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

static char	*expand_variable(char *str, int *index, t_env *env, t_garbage **garbage)
{
	char	*res;
	char	*var_name;
	int		start;

	(*index)++;
	start = (*index);
	if (str[*index] == '?')
	{
		(*index)++;
		return (ft_strdup("exit status here\n", garbage));
	}
	if (str[*index] == '\0' || !is_valid_var(str[*index]))
		return (ft_strdup("$", garbage));
	var_name = extract_var_name(str, index, garbage);
	res = ft_getenv(var_name, &env);
	return (res);
}

char	*ft_replace_dollar(char *str, t_env *env, t_garbage **garbage)
{
	char	*res;
	int		index;
	int		start;

	res = NULL;
	index = 0;
	while (str[index])
	{
		start = index;
		while (str[index])
		{
			if (str[index] == '$')
			{
				if (start != index)
					res = ft_strjoin(res, ft_strldup(&str[start], index - start, garbage), garbage);
				break ;
			}
			index++;
			if (str[index] == '\0')
				res = ft_strjoin(res, ft_strldup(&str[start], index - start, garbage), garbage);
		}
		if (str[index] && str[index] == '$')
			res = ft_strjoin(res, expand_variable(str, &index, env, garbage), garbage);
	}
	return (res);
}
