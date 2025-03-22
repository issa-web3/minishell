/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/22 17:59:23 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(char **arr, int n)
{
    int i = 0;
    while (i < n - 1)
    {
        int j = 0;
        while (j < n - i - 1)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0) 
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
	char	*key;
	char	*value;

	i = 0;
	while (env_vars[i])
	{
		key = env_vars[i];
		value = ft_strchr(key, '=');
		if (value)
		{
			*(value++) = '\0';
			if (key[0] != '_' && key[1] != '=')
				printf("declare -x %s=\"%s\"\n", key, value);
		}
		else
			printf("declare -x %s\n", key);
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