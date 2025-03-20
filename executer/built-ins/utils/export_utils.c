/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/20 23:24:56 by test             ###   ########.fr       */
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

char **sort_export(t_env *head, t_data *data, t_alloc **head_ch)
{
    char    **env_vars;
    t_env   *current;
    int count;
    int i;

    (void) data;
    count = 0;
    current = head;
    while (current)
    {
        if (current->env_var) 
            count++;
        current = current->next;
    }
    env_vars = ft_malloc2((count + 1) * sizeof(char *), head_ch);
    current = head;
    i = 0;
    while (current)
    {
        if (current->env_var) 
            env_vars[i++] = ftt_strdup2(current->env_var, head_ch);
        current = current->next;
    }
    env_vars[i] = NULL;
    bubble_sort(env_vars, count);
    return (env_vars);
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