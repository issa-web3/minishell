/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/08 11:10:03 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// export PATH=dfgdfhh
// export PATH+=dfgdfhh

void	ft_export(char **cmd, t_env *my_env)
{
	t_env	*to_export;
	char	**parsed;
	char	append;

	if (cmd[1] == NULL)
		return ; // segma
	parsed = ft_split(cmd[1], '=', NULL);
	if (parsed == NULL)
		return ;
	if (parsed[0] == NULL)
		return ;
	if (parsed[1] == NULL)
		return ;
	append = 0;
	if (parsed[0][ft_strlen(parsed[0]) - 1] == '+')
		(parsed[0][ft_strlen(parsed[0]) - 1] = 0, append = 1);
	to_export = ft_getenv(parsed[0], my_env);
	// append or overwrite
	if (to_export == NULL)
		append_env(&my_env, get_last_env(my_env), new_env_var(parsed));
	else if (append)
		to_export->value = ft_strjoin(to_export->value, parsed[1]);
	else
		(free(to_export->value), to_export->value = parsed[1]);
}
