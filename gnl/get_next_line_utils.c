/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line_utils.c							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ioulkhir <ioulkhir@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/20 16:13:58 by ioulkhir		  #+#	#+#			 */
/*   Updated: 2024/12/10 10:23:01 by ioulkhir		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"

t_data_chunk	*new_chunk(void)
{
	t_data_chunk	*new;

	new = malloc(sizeof(t_data_chunk));
	if (new == NULL)
		return (new);
	new->buffer[0] = 0;
	new->next = NULL;
	new->lst_size = 1;
	return (new);
}

t_data_chunk	*append_chunk_lst(t_data_chunk **head, t_data_chunk *tail)
{
	if (*head == NULL)
		return (*head = new_chunk());
	((*head)->lst_size)++;
	return (tail->next = new_chunk());
}

long	check_new_line(char *buffer)
{
	long	i;

	i = 0;
	while (i <= BUFFER_SIZE && buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

long	calc_result_size(t_data_chunk *head, t_data_chunk *tail
					, long bytes_read, long lst_size)
{
	long		result_size;
	int			new_line_index;

	new_line_index = check_new_line(head->buffer);
	if (new_line_index == -1)
		result_size = head->rest_len;
	else
		return (new_line_index + 1);
	if (lst_size > 2)
		result_size += (lst_size - 2) * BUFFER_SIZE;
	if (tail && head != tail)
		result_size += bytes_read;
	return (result_size);
}

long	ft_strcpy(char *src, char *dst)
{
	long	i;

	i = 0;
	while (i <= BUFFER_SIZE && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	src[0] = 0;
	return (i);
}
