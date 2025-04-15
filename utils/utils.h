/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:04:41 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/15 07:28:16 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../structs.h"
# include "../executer/exec_structs.h"
# include "../executer/executer.h"

// part 1
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1, t_garbage **my_garbage);
char		*ft_strdup_wg(const char *s1, t_garbage **my_garbage);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			is_sep(char set, char c);

// part 2
int			count_words(const char *str, char c);
char		**ft_split(char *s, char c, t_garbage **my_garbage);
char		**ft_split_without_garbage(char *s, char c);
char		*ft_strjoin(char *s1, char *s2, t_garbage **my_garbage);
char	    *ft_strjoin_without_garbage(char *s1, char *s2, t_garbage **my_garbage);
char		*ft_itoa(int n, t_garbage **g);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

// linked list
void		ft_lstadd_front(t_2_exec **lst, t_2_exec *new_node);
int			ft_lstsize(t_2_exec *lst);
t_2_exec	*ft_lstlast(t_2_exec *lst);

// env
t_env		*copy_env(char **env, t_garbage **my_garbage);
t_env		*ft_getenv(char *name, t_env **my_env);
t_env		*new_env_var(char **data);
t_env		*append_env(t_env **head, t_env *tail, t_env *new_env);
t_env		*get_last_env(t_env **my_env);
void		del_env_var(t_env *env_var, t_env **my_env);
void		clear_env(t_env **my_env);
char		**format_env(t_env **my_env, t_garbage **my_garbage);
int			env_len(t_env *curr);

// exit status
int			get_exit_status(void);
void		set_exit_status(int new);
void		set_and_exit(int new);
void		wait_last_pid(pid_t last_pid);

#endif