/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:25:11 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/22 07:10:16 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

t_env	*copy_env(char **env, t_garbage **my_garbage)
{
	t_env		*my_env;
	t_env		*tail;
	char		*data[2];
	int			i;

	i = 0;
	my_env = NULL;
	tail = NULL;
	while (env[i])
	{
		data[0] = ft_strdup(env[i], my_garbage);
		data[1] = ft_strchr(data[0], '=');
		if (data[1])
			*(data[1]++) = '\0';
		data[1] = ft_strdup(data[1], my_garbage);
		tail = append_env(&my_env, tail, new_env_var(data));
		if (tail == NULL)
			return (clear_all(my_garbage), set_and_exit(EXIT_FAILURE), NULL);
		remove_ptr_from_garbage(my_garbage, data[0]);
		remove_ptr_from_garbage(my_garbage, data[1]);
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
	result = ft_malloc((i + 1) * (sizeof(char *)), my_garbage);
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

	if (!my_env)
		return ;
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
