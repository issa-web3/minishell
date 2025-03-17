/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/17 17:23:14 by ioulkhir         ###   ########.fr       */
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

#include <sys/types.h>
#include <sys/wait.h>

# include "utils/utils.h"
# include "structs.h"
# include "executer/executer.h"
# include "parser/parser.h"

// exit status
# define SYNTAX_ERR 2
# define COMMAND_NOT_FOUND 127
# define NO_SUCH_FILE_OR_DIR 1

#endif