/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/03/13 10:10:19 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCTS_H
# define EXEC_STRUCTS_H

#include "../structs.h"

// built-ins
typedef struct s_builtin
{
	void	(*func)(t_2_exec *, t_env **, t_garbage **, char is_child);
	char	*name;
}				t_builtin;

typedef struct s_process_info
{
	int		process_idx;
	int		process_num;
	int		fork_response;
}				t_process_info;

#endif