/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/22 18:11:05 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void swap(char **a, char **b)
{
    char *temp;

	temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(char **arr, int n)
{
    int	i;
    int	j;

    i = 0;
    while (i < n - 1)
    {
        j = 0;
        while (j < n - i - 1)
        {
            if (ft_strcmp(arr[j], arr[j + 1]) > 0) 
                swap(&arr[j], &arr[j + 1]);
            j++;
        }
        i++;
    }
}

char **sort_export(t_env **my_env, t_garbage **my_garbage)
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
	while (env_vars[i])
	{
		name = env_vars[i];
		value = ft_strchr(name, '=');
		if (value)
		{
			*(value++) = '\0';
			if (ft_strncmp(name, "_=", 2))
				printf("declare -x %s=\"%s\"\n", name, value);
		}
		else
			printf("declare -x %s\n", name);
		i++;
	}
}

int is_valid(const char *str)
{
    int i = 1;

    if (!str || !*str)
        return 0;
    if (!(isalpha(str[0]) || str[0] == '_'))
        return 0;
    while (str[i] && str[i] != '=')
    {
        if (isalnum(str[i]) || str[i] == '_')
        {
            i++;
            continue;
        }
        if (str[i] == '+' && str[i+1] == '=')
        {
            i++;
            break;
        }
        return (0);
    }  
    return (1);
}