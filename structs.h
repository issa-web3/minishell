/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/11 21:41:06 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_file
{
	char			*name;
	t_token_type	type;
	struct s_file	*next;
}			t_file;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}			t_token;

typedef struct s_garbage
{
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

// ls -l -a < in1 > out1 << here1 | grep "a" > out | end
typedef struct s_2_exec
{
	char			**cmd;
	t_file			*files;
	struct s_2_exec	*next;
}				t_2_exec;

#endif