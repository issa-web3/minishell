/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/21 00:26:59 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# include "../minishell.h"
# include "exec_structs.h"

// big function
void			execute(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
int				create_children_pipes(pid_t (*pipes)[2],
					t_process_info *init_pi);
int				exec_builtin(t_2_exec *data, t_env **my_env, t_garbage **my_garbage,
					char is_child);
void			close_prev_pipes(pid_t (*pipes)[2], int nth_process);
void			distribute_tasks(t_process_info pi, pid_t (*pipes)[2],
					t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
void			exec_by_idx(t_2_exec *data, t_env **my_env,
					t_garbage **my_garbage);
char			*get_path(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
char			redirections(t_file **files, char redirect);

// built-in
void			ft_cd(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child);
void			ft_echo(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child);
void			ft_env(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child);
void			ft_exit(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child);
void			ft_export(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child);
void			ft_pwd(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child);
void			ft_unset(t_2_exec *data, t_env **my_env, t_garbage **my_garbage, char is_child);

// garbage utils
void			clear_garbage(t_garbage **my_garbage);
t_garbage		*append_garbage(t_garbage **my_garbage, void *ptr);
void			*ft_malloc(size_t size, t_garbage **my_garbage);

// protected proxies
int				ft_pipe(int *arr);
int				ft_dup2(int a, int b);
pid_t			ft_fork(void);
int				ft_open(char *filename, int mode);

#endif