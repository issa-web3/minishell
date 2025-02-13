/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.h									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ioulkhir <ioulkhir@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/08 09:52:46 by ioulkhir		  #+#	#+#			 */
/*   Updated: 2024/12/10 10:22:13 by ioulkhir		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
#include "../minishell.h"

typedef struct s_data_chunk
{
	char				buffer[BUFFER_SIZE + 1];
	long				rest_len;
	long				lst_size;
	struct s_data_chunk	*next;
}	t_data_chunk;

char			*get_next_line(int fd);
long			check_new_line(char *buffer);
long			calc_result_size(t_data_chunk *head,
					t_data_chunk *tail,
					long bytes_read, long lst_size);
char			*lst_to_str(t_data_chunk **head, t_data_chunk *tail,
					long bytes_read, t_data_chunk *new_head);
t_data_chunk	*new_chunk(void);
t_data_chunk	*append_chunk_lst(t_data_chunk **head, t_data_chunk *tail);
long			ft_strcpy(char *src, char *dst);
void			copy_lst_and_free(t_data_chunk **head, char *result);

#endif