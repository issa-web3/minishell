/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/06 15:34:56 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	main(int ac, char **av)
{
	int	i;
	int	end;

	if (ac == 1)
		return (write(1, "\n", 1), 0);
	i = 0;
	end = ft_strcmp(av[1], "-n");
	!end && i++;
	while (++i < ac)
	{
		write(1, av[i], ft_strlen(av[i]));
		i != ac - 1 && write(1, " ", 1);
	}
	(end) && (write(1, "\n", 1));
}
