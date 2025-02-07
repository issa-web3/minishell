/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:50:34 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/07 11:40:17 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char **cmd, char **env)
{
	chdir("/");
	char buffer[1024];
	getcwd(buffer, 1024);
	printf("%s\n", buffer);
	exit(EXIT_SUCCESS);
}
