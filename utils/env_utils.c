/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:25:11 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/13 11:41:18 by ioulkhir         ###   ########.fr       */
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

t_env	*new_env_var(char **data)
{
	t_env	*my_env;

	my_env = malloc(sizeof(t_env));
	if (my_env == NULL)
		return (perror("malloc"), NULL);
	my_env->name = data[0];
	my_env->value = data[1];
	if (ft_strcmp(data[0], "SHLVL") == 0)
	{
		my_env->value = ft_itoa(ft_atoi(data[1]) + 1);
		free(data[1]);
	}
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
		env_var->next = NULL;
		clear_env(&env_var);
		return ;
	}
	prev_env = (*my_env);
	while (prev_env && env_var != prev_env->next)
		prev_env = prev_env->next;
	prev_env->next = env_var->next;
	env_var->next = NULL;
	clear_env(&env_var);
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

	(curr = *my_env, i = 0);
	while (curr)
		(i++, curr = curr->next);
	if (i == 0)
		return (NULL);
	result = ft_malloc(i * (sizeof(char *) + 1), my_garbage);
	if (result == NULL)
		return (NULL);
	(curr = *my_env, i = 0);
	while (curr)
	{
		result[i] = ft_strjoin(curr->name,
			ft_strjoin("=", curr->value,
				my_garbage), my_garbage);
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
