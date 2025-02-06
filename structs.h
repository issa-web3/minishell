/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/02/04 14:15:43 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_file
{
	char	*name;
	int		type;
}			t_file;

typedef struct s_token
{
	char	*token;
	int		type;
}			t_token;

typedef struct s_garbage
{
	void			*ptr;
	struct s_garbage *next;
}					t_garbage;

// ls -l -a < in1 > out1 << here1 | grep "a" > out | end
typedef struct s_2_exec
{
	char			**cmd;
	t_file			*files;
	char			*infile;
	char			*outfile;
	struct s_2_exec	*next;
}				t_2_exec;

#endif