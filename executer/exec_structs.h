/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/04/14 15:55:14 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCTS_H
# define EXEC_STRUCTS_H

#include "../structs.h"

typedef pid_t t_pipe[2];

typedef struct s_process_info
{
	int		process_idx;
	int		process_num;
	int		fork_response;
}				t_process_info;

typedef struct s_export_data
{
	char	**parsed;
	char	is_valid;
	char	append;
}				t_export_data;

#endif