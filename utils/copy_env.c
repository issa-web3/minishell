/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:25:11 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/08 11:09:14 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_env	*get_last_env(t_env *my_env)
{
	while (my_env && my_env->next)
		my_env = my_env->next;
	return (my_env);
}

t_env	*new_env_var(char **data)
{
	t_env	*my_env;

	my_env = malloc(sizeof(t_env));
	if (my_env == NULL)
		return (NULL);
	my_env->name = data[0];
	my_env->value = data[1];
	my_env->next = NULL;
	return (my_env);
}

t_env	*append_env(t_env **head, t_env *tail, t_env *new_env)
{
	if (tail == NULL)
		return (*head = new_env);
	else
		return (tail->next = new_env);
	return (new_env);
}

t_env	*copy_env(char **env)
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
		data = ft_split(env[i], '=', NULL);
		if (data == NULL)
			return (NULL); // malloc
		tail = append_env(&my_env, tail, new_env_var(data));
		if (tail == NULL)
			return (NULL); // malloc
		i++;
	}
	return (my_env);
}
