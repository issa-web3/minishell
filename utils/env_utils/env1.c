/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:25:11 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/16 12:01:51 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

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
