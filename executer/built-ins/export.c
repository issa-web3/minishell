/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/14 08:52:42 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child)
{
	t_env	*to_export;
	char	**parsed;
	char	append;

	(void)is_child;
	if (data->cmd[1] == NULL)
		return ;
	parsed = ft_split_without_garbage(data->cmd[1], '=');
	if (parsed == NULL || parsed[0] == NULL || parsed[1] == NULL)
	{
		write(2, "syntax issue\n", 13);
		return ;
	}
	append = 0;
	if (parsed[0][ft_strlen(parsed[0]) - 1] == '+')
	{
		parsed[0][ft_strlen(parsed[0]) - 1] = 0;
		append = 1;
	}
	to_export = ft_getenv(parsed[0], my_env);
	if (to_export == NULL)
		append_env(my_env, get_last_env(my_env), new_env_var(parsed));
	else if (append)
		to_export->value = ft_strjoin(to_export->value, parsed[1], my_garbage);
	else
		(to_export->value = parsed[1]);

}
