/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/23 02:12:31 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	no_args(t_env **my_env, t_garbage **my_garbage)
{
	char	**env_vars;

	env_vars = sort_export(my_env, my_garbage);
	print_sorted_env(env_vars);
}

void	ft_export(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage, char is_child)
{
	t_env	*to_export;
	char	*parsed[2];
	char	*old_val;
	char	*rm_plus;
	char	*sep;
	char	append;
	int		i;

	(void)is_child;
	(void)my_garbage;
	i = 1;
	if (data->cmd[i] == NULL)
		no_args(my_env, my_garbage);
	while (data->cmd[i])
	{
		if (!is_valid(data->cmd[i]))
		{
			write(2, "export: '", 9);
			write(2, data->cmd[i], ft_strlen(data->cmd[i]));
			write(2, "': not a valid identifier\n", 27);
			set_exit_status(GENERIC_ERR);
		}
		sep = ft_strchr(data->cmd[i], '=');
		if (sep)
			*(sep++) = 0;
		parsed[0] = ft_strdup_wg(data->cmd[i]);
		parsed[1] = ft_strdup_wg(sep);
		if (parsed[0] == NULL || (parsed[1] == NULL && sep))
		{
			clear_all(my_garbage);
			exit(EXIT_FAILURE);
		}
		rm_plus = &parsed[0][ft_strlen(parsed[0]) - 1];
		append = *rm_plus == '+';
		*rm_plus -= *rm_plus * append;
		
		to_export = ft_getenv(parsed[0], my_env);
		if (to_export == NULL)
			append_env(my_env, get_last_env(my_env), new_env_var(parsed));
		else
		{
			old_val = to_export->value;
			if (append)
			{
				to_export->value = ft_strjoin_without_garbage(to_export->value, parsed[1]);
				free(parsed[1]);
			}
			else
			{
				if (parsed[1])
					to_export->value = parsed[1];
			}
			if (old_val != to_export->value)
				free(old_val);
		}
		i++;
	}
}
