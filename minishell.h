/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/09 10:45:39 by ioulkhir         ###   ########.fr       */
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

#include <sys/types.h>
#include <sys/wait.h>

# include "utils/utils.h"
# include "structs.h"
# include "executer/executer.h"
# include "parser/parser.h"

// exit statuses
#define GENERIC_ERR 1
#define ERR 2
#define NO_SUCH_FILE_OR_DIR 1
#define COMMAND_NOT_FOUND 127
#define SYNTAX_ERR 2
#define INVALID_EXIT_STATUS 126
#define TERMINATED_BY_SIGNAL 128

#endif