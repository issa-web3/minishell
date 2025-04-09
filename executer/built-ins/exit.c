/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/09 10:43:41 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exit_arg	ft_atol(char *str)
{
	t_exit_arg	result;
	int			sign;
	int			i;

	result.val = 0;
	result.err = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = (str[i++] == '+') * 2 - 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result.val > (LONG_MAX - (str[i] - '0')) / 10)
		{
			result.err = 1;
			sign = 1;
			break ;
		}
		result.val = result.val * 10 + (str[i] - '0');
		i++;
	}
	result.err = str[i] != '\0';
	result.val *= sign;
	return (result);
}

int	change_exit_status(char **args)
{
	t_exit_arg	tmp;
	int			ac;

	ac = -1;
	while (args[++ac])
		;
	if (ac == 0)
		return (set_exit_status(EXIT_SUCCESS), 0);
	tmp = ft_atol(args[0]);
	if (tmp.err)
	{
		write(2, "exit: ", 6);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": numeric argument required\n", 28);
		return (set_exit_status(ERR), 0);
	}
	if (ac == 1)
		return (set_exit_status(tmp.val % 256), 0);
	if (ac > 1)
		return (write(2, "exit: too many arguments\n", 25), set_exit_status(EXIT_FAILURE), -1);
	return (set_exit_status(EXIT_SUCCESS), 0);
}

void	ft_exit(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	int	result;

	(void)my_env;
	if (data->p_info.fork_response == 314)
		write(1, "exit\n", 5);
	result = change_exit_status(data->cmd + 1);
	if (result != -1)
	{
		clear_all(my_garbage);
		exit(get_exit_status());
	}
}
