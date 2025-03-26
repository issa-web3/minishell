/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/03/26 04:58:08 by test             ###   ########.fr       */
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
			result.val = 2;
			result.err = 1;
			sign = 1;
			break ;
		}
		result.val = result.val * 10 + (str[i] - '0');
		i++;
	}
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
	if (ac == 1)
	{
		tmp = ft_atol(args[0]);
		if (tmp.err)
		{
			write(2, "exit: ", 6);
			write(2, args[0], ft_strlen(args[0]));
			write(2, ": numeric argument required\n", 28);
		}
		return (set_exit_status(tmp.val % 256), 0);
	}
	if (ac > 1)
		return (write(2, "exit: too many arguments\n", 25), set_exit_status(1), -1);
	return (set_exit_status(0), 0);
}

void	ft_exit(t_2_exec *data, t_env **my_env,
		t_garbage **my_garbage)
{
	int	result;

	(void)my_env;
	if (data->pi.fork_response == 314)
		write(1, "exit\n", 5);
	result = change_exit_status(data->cmd + 1);
	if (result != -1)
	{
		clear_all(my_garbage);
		exit(get_exit_status());
	}
}
