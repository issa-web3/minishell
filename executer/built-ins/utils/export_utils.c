/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/18 17:35:59 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**sort_export(t_env **my_env, t_garbage **my_garbage)
{
	char	**env_vars;

	env_vars = format_env(my_env, my_garbage);
	bubble_sort(env_vars, env_len(*my_env));
	return (env_vars);
}

void	print_sorted_env(char **env_vars)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (env_vars && env_vars[i])
	{
		name = env_vars[i];
		value = ft_strchr(name, '=');
		if (value)
		{
			*(value++) = '\0';
			if (ft_strcmp(name, "_"))
				printf("declare -x %s=\"%s\"\n", name, value);
		}
		else
			printf("declare -x %s\n", name);
		i++;
	}
}

int	is_valid(const char *str)
{
	int	i;

	i = 1;
	if (!str || !*str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (
		(str[i] == '+' && str[i + 1] == '=')
		|| str[i] == '='
		|| str[i] == '\0'
	);
}

t_xprt_data	not_valid_identifier(char *arg)
{
	t_xprt_data	data;

	write(2, "export: '", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
	set_exit_status(GENERIC_ERR);
	data.parsed = NULL;
	data.append = 0;
	data.is_valid = 0;
	return (data);
}
