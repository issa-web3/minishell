/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 17:30:02 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	no_args(t_2_exec *data, t_env **my_env, t_garbage **my_garbage)
{
	char	**env_vars;

	if (data->cmd[1] == NULL)
	{
		env_vars = sort_export(my_env, my_garbage);
		print_sorted_env(env_vars);
	}
	return (1);
}

t_xprt_data	export_parse_data(char *arg, t_garbage **my_garbage)
{
	char			**parsed;
	char			*rm_plus;
	char			*sep;
	char			append;
	t_xprt_data		data;

	data.is_valid = 1;
	if (!is_valid(arg))
		return (not_valid_identifier(arg));
	sep = ft_strchr(arg, '=');
	if (sep)
		*(sep++) = 0;
	parsed = ft_malloc(2 * sizeof(char *), my_garbage);
	parsed[0] = ft_strdup(arg, my_garbage);
	parsed[1] = ft_strdup(sep, my_garbage);
	rm_plus = &parsed[0][ft_strlen(parsed[0]) - 1];
	append = *rm_plus == '+';
	*rm_plus -= *rm_plus * append;
	data.parsed = parsed;
	data.append = append;
	data.is_valid = 1;
	return (data);
}

char	*path_special_case(char **data, t_env *to_export,
		char *d_path, t_garbage **my_garbage)
{
	if (to_export == NULL && data[1] == NULL && !ft_strcmp(data[0], "PATH"))
		return (ft_strdup(d_path, my_garbage));
	return (data[1]);
}

void	modify_env_var(t_env *to_export, char append_mode,
		char **parsed, t_garbage **my_garbage)
{
	t_garbage	*new_garbage;

	new_garbage = append_garbage(my_garbage, to_export->value);
	if (new_garbage == NULL)
		(perror("malloc"), clear_all(my_garbage), set_and_exit(EXIT_FAILURE));
	if (append_mode)
		to_export->value = ft_strjoin(to_export->value, parsed[1], my_garbage);
	else
	{
		if (parsed[1])
			to_export->value = parsed[1];
	}
	remove_ptr_from_garbage(my_garbage, to_export->value);
}

void	ft_export(t_2_exec *data, t_env **my_env,
		t_garbage **my_g)
{
	t_env			*to_export;
	t_xprt_data		export_data;
	char			**parsed;
	int				i;

	i = no_args(data, my_env, my_g);
	while (data->cmd[i])
	{
		export_data = export_parse_data(data->cmd[i], my_g);
		if (!export_data.is_valid && i++ > 0)
			continue ;
		to_export = ft_getenv(export_data.parsed[0], my_env);
		parsed = export_data.parsed;
		parsed[1] = path_special_case(parsed, to_export, *data->d_path, my_g);
		if (to_export == NULL && ft_strcmp(data->cmd[0], "modify"))
		{
			if (!append_env(my_env, get_last_env(my_env), new_env_var(parsed)))
				(clear_all(my_g), set_and_exit(EXIT_FAILURE));
			remove_ptr_from_garbage(my_g, parsed[0]);
			remove_ptr_from_garbage(my_g, parsed[1]);
		}
		else if (to_export != NULL)
			modify_env_var(to_export, export_data.append, parsed, my_g);
		i++;
	}
}
