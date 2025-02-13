/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:25:11 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/13 14:28:17 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_env	*get_last_env(t_env **my_env)
{
	t_env	*curr;

	curr = *my_env;
	while (curr && curr->next)
		curr = curr->next;
	return (curr);
}

t_env	*new_env_var(char **data, t_garbage **my_garbage)
{
	t_env	*my_env;

	my_env = ft_malloc(sizeof(t_env), my_garbage);
	if (my_env == NULL)
		return (NULL);
	my_env->name = data[0];
	my_env->value = data[1];
	my_env->next = NULL;
	return (my_env);
}

void	del_env_var(t_env *env_var, t_env **my_env)
{
	t_env	*prev_env;

	if (env_var == NULL)
		return ;
	if (env_var == *my_env)
	{
		*my_env = (*my_env)->next;
		return ;
	}
	prev_env = (*my_env);
	while (prev_env && env_var != prev_env->next)
		prev_env = prev_env->next;
	prev_env->next = env_var->next;
}

t_env	*append_env(t_env **head, t_env *tail, t_env *new_env)
{
	if (tail == NULL)
		return (*head = new_env);
	else
		return (tail->next = new_env);
	return (new_env);
}

t_env	*copy_env(char **env, t_garbage **my_garbage)
{
	t_env	*my_env;
	t_env	*tail;
	char	**data;
	int		i;

	i = 0;
	while (env[i])
		i++;
	i = 0;
	my_env = NULL;
	tail = NULL;
	while (env[i])
	{
		data = ft_split(env[i], '=', my_garbage);
		if (data == NULL)
			return (NULL); // malloc
		tail = append_env(&my_env, tail, new_env_var(data, my_garbage));
		if (tail == NULL)
			return (NULL); // malloc
		i++;
	}
	return (my_env);
}
