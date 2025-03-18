/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/18 14:46:57 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	no_args(t_2_exec *data, t_env **my_env,
	t_garbage **my_garbage, char is_child)
{
	if (data->cmd[1])
		return ;
	ft_env(data, my_env, my_garbage, is_child);
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
	no_args(data, my_env, my_garbage, is_child);
	while (data->cmd[i])
	{
		sep = ft_strchr(data->cmd[i], '=');
		if (sep)
			*(sep++) = 0;
		parsed[0] = ft_strdup_wg(data->cmd[i]);
		parsed[1] = ft_strdup_wg(sep);
		if (parsed[0] == NULL || (parsed[1] == NULL && sep))
			return ;
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
