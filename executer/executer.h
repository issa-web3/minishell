/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/02/08 10:07:46 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# include "../minishell.h"
# include "exec_structs.h"

void	execute(t_2_exec *data, t_env *my_env);
void	exec_builtin(char **cmd, t_env *my_env, char exit_flag);
void	exec_by_idx(t_2_exec *data, t_env *my_env, int i);
char	*get_path(char *cmd, t_env *my_env);

// built-in

void    ft_cd(char **cmd, t_env *my_env);
void    ft_echo(char **cmd, t_env *my_env);
void    ft_env(char **cmd, t_env *my_env);
void    ft_exit(char **cmd, t_env *my_env);
void    ft_export(char **cmd, t_env *my_env);
void    ft_pwd(char **cmd, t_env *my_env);
void    ft_unset(char **cmd, t_env *my_env);

// parsing
t_2_exec	*parser(int ac, char **av, t_env *my_env, char *line);


#endif