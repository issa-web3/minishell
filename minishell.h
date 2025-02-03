/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-03 12:59:53 by khoukouj         ###   ########.1337.ma  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "executer/executer.h"

typedef struct s_2_exec
{
	char			**cmd; // command and args
	char			*file;
	struct s_2_exec	*next;
}				t_2_exec;


//parsing

#endif