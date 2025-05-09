/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/23 12:06:39 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>

# include "../minishell.h"
# include "exec_structs.h"

// big function
void		execute(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
void		fork_and_pipe(t_pipe *pipes, t_process_info *init_pi,
				t_garbage **my_garbage);
int			exec_builtin(t_2_exec *data, t_env **my_env,
				t_garbage **my_garbage);
void		close_useless_pipes(t_pipe *pipes, int nth_process);
void		execute_task_by_idx(t_pipe *pipes, t_2_exec *data, t_env **my_env,
				t_garbage **my_garbage);
void		exec_by_idx(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
char		*get_path(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
char		redirections(t_file **files, char redirect);

// built-in
void		ft_cd(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
void		ft_echo(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
void		ft_env(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
void		ft_exit(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
void		ft_export(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
void		ft_pwd(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);
void		ft_unset(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);

// built-in utils
int			is_valid(const char *str);
t_xprt_data	not_valid_identifier(char *arg);
void		print_sorted_env(char **env_vars);
char		**sort_export(t_env **my_env, t_garbage **my_garbage);

// garbage utils
void		clear_garbage(t_garbage **my_garbage);
t_garbage	*append_garbage(t_garbage **my_garbage, void *ptr);
void		*ft_malloc(size_t size, t_garbage **my_garbage);
void		remove_ptr_from_garbage(t_garbage **my_garbage, void *ptr);

// protected proxies
int			ft_pipe(int *arr);
int			ft_dup(int a);
int			ft_dup2(int a, int b);
pid_t		ft_fork(void);
int			ft_open(char *filename, int mode);

// leaks
void		clear_all(t_garbage **my_garbage);

// path utils
void		is_command_not_found(t_2_exec *data, char *path);
char		*check_dir(t_2_exec *data);
char		*check_access_directly(char *cmd);
char		*check_the_path_env(t_2_exec *data, t_env **my_env,
				t_garbage **my_garbage);
char		**get_paths(t_2_exec *data, t_env **my_env, t_garbage **my_garbage);

// pwd
void		update_pwd(t_2_exec *data, t_garbage **my_garbage);

#endif