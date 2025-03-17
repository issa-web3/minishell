/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/17 14:28:15 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage, char is_child)
{
	t_env	*to_export;
	char	**parsed;
	char	*old_val;
	char	*rm_plus;
	char	append;
	int		i;

	(void)is_child;
	(void)my_garbage;
	i = 1;
	while (data->cmd[i])
	{
		parsed = ft_split_without_garbage(data->cmd[i], '=');
		if (parsed == NULL)
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
				to_export->value = parsed[1];
			free(old_val);
		}
		i++;
	}
}
