/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/17 17:50:04 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	no_args(t_env **my_env, t_garbage **my_garbage)
{
	char	**env_vars;

	env_vars = sort_export(my_env, my_garbage);
	print_sorted_env(env_vars);
}

t_export_data	export_parse_data(char *arg, t_garbage **my_garbage)
{
	char			**parsed;
	char			*rm_plus;
	char			*sep;
	char			append;
	int				i;
	t_export_data	data;

	data.is_valid = 1;
	if (!is_valid(arg))
	{
		write(2, "export: '", 9);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 27);
		set_exit_status(GENERIC_ERR);
		data.parsed = NULL;
		data.append = append;
		data.is_valid = 0;
		return (data);
	}
	sep = ft_strchr(arg, '=');
	if (sep)
		*(sep++) = 0;
	parsed = ft_malloc(2 * sizeof(char *), my_garbage);
	parsed[0] = ft_strdup(arg, my_garbage);
	parsed[1] = ft_strdup(sep, my_garbage);
	if (parsed[0] == NULL || (parsed[1] == NULL && sep))
	{
		clear_all(my_garbage);
		set_and_exit(EXIT_FAILURE);
	}
	rm_plus = &parsed[0][ft_strlen(parsed[0]) - 1];
	append = *rm_plus == '+';
	*rm_plus -= *rm_plus * append;
	data.parsed = parsed;
	data.append = append;
	data.is_valid = 1;
	return (data);
}

char	*path_special_case(char **data, t_env *to_export,
		char *default_path, t_garbage **my_garbage)
{
	if (to_export == NULL && data[1] == NULL && !ft_strcmp(data[0], "PATH"))
		return (ft_strdup(default_path, my_garbage));
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
		t_garbage **my_garbage)
{
	t_env			*to_export;
	t_export_data	export_data;
	char			*old_val;
	char			**parsed;
	int				i;

	(void)my_garbage;
	i = 1;
	if (data->cmd[i] == NULL)
		no_args(my_env, my_garbage);
	while (data->cmd[i])
	{
		export_data = export_parse_data(data->cmd[i], my_garbage);
		if (!export_data.is_valid && i++ > 0)
			continue ;
		to_export = ft_getenv(export_data.parsed[0], my_env);
		parsed = export_data.parsed;
		parsed[1] = path_special_case(parsed, to_export, *data->default_path, my_garbage);
		if (to_export == NULL)
		{
			if (append_env(my_env, get_last_env(my_env), new_env_var(parsed)) == NULL)
				(clear_all(my_garbage), set_and_exit(EXIT_FAILURE));
			remove_ptr_from_garbage(my_garbage, parsed[0]);
			remove_ptr_from_garbage(my_garbage, parsed[1]);
		}
		else
			modify_env_var(to_export, export_data.append, parsed, my_garbage);
		i++;
	}
}
