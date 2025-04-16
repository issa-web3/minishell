/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/16 13:36:00 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>

# include <sys/types.h>
# include <sys/wait.h>

# include "utils/utils.h"
# include "structs.h"
# include "executer/executer.h"
# include "parser/parser.h"

// global var
extern int	g_signals;
// exit statuses
# define GENERIC_ERR 1
# define ERR 2
# define NO_SUCH_FILE_OR_DIR 1
# define COMMAND_NOT_FOUND 127
# define SYNTAX_ERR 2
# define INVALID_EXIT_STATUS 126
# define TERMINATED_BY_SIGNAL 128
# define TERMINATED_BY_CNTL_C 130

// main utils
char	*get_default_path(char *str, t_env **my_env);
void	init(t_garbage **my_garbage, t_env **my_env,
			char **env, char **default_path);
char	*ft_readline(t_env **my_env);
void	init_garbage(t_garbage **my_garbage, t_env **my_env, t_2_exec *data);

#endif