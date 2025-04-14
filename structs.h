/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/14 16:23:26 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "executer/exec_structs.h"

// env
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
	APPEND,
	REDIR_INPUT,
	REDIR_OUTPUT,
	HERE_DOC,
	OUT_FILE,
	IN_FILE,
	APPEND_FILE,
}	t_token_type;

typedef struct s_file
{
	char			*name;
	t_token_type	type;
	struct s_file	*next;
}			t_file;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
}			t_token;

typedef struct s_heredoc
{
	char	*line;
	char	*del;
	int		is_expand;
}	t_heredoc;

// ls -l -a < in1 > out1 << here1 | grep "a" > out | end
typedef struct s_2_exec
{
	char			**cmd;
	t_file			*files;
	t_process_info	p_info;
	char			**default_path;
	char			*pwd;
	struct s_2_exec	*next;
}				t_2_exec;

typedef struct s_garbage
{
	t_2_exec		*data;
	t_env			**my_env;
	void			*ptr;
	struct s_garbage *next;
}					t_garbage;
//this struct is just for the quote removal stuff
typedef struct s_extract_info
{
	int	start;
	int	length;
}	t_extract_info;
// also this one same as before 
typedef struct s_indices
{
	int	str_index;
	int	result_index;
}	t_indices;

typedef struct s_expand
{
	char	*value;
	int		is_expand;
	struct s_expand *next;
}	t_expand;

// built-ins
typedef struct s_builtin
{
	void	(*func)(t_2_exec *, t_env **, t_garbage **);
	char	*name;
}				t_builtin;

typedef struct s_exit_arg
{
	long	val;
	char	err;
}				t_exit_arg;

#endif