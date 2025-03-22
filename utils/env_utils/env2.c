/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:25:11 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/22 18:03:56 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

t_env	*copy_env(char **env)
{
	t_env		*my_env;
	t_env		*tail;
	char		**data;
	int			i;

	i = 0;
	while (env[i])
		i++;
	i = 0;
	my_env = NULL;
	tail = NULL;
	while (env[i])
	{
		data = ft_split_without_garbage(env[i], '=');
		if (data == NULL)
			return (clear_env(&my_env), NULL);
		tail = append_env(&my_env, tail, new_env_var(data));
		if (tail == NULL)
			return (clear_env(&my_env), NULL);
		i++;
	}
	return (my_env);
}

char	**format_env(t_env **my_env, t_garbage **my_garbage)
{
	char	**result;
	t_env	*curr;
	size_t	i;

	1 && (curr = *my_env, i = 0);
	while (curr)
		1 && (i++, curr = curr->next);
	if (i == 0)
		return (NULL);
	result = ft_malloc(i * (sizeof(char *) + 1), my_garbage);
	1 && (curr = *my_env, i = 0);
	while (curr)
	{
		if (curr->value)
			result[i] = ft_strjoin(curr->name, "=", my_garbage);
		else
			result[i] = ft_strjoin(curr->name, NULL, my_garbage);
		result[i] = ft_strjoin(result[i], curr->value, my_garbage);
		curr = curr->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	clear_env(t_env **my_env)
{
	t_env	*curr;
	t_env	*next;

	curr = *my_env;
	while (curr)
	{
		next = curr->next;
		free(curr->name);
		free(curr->value);
		free(curr);
		curr = next;
	}
	*my_env = NULL;
}
