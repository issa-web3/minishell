/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ioulkhir <ioulkhir@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/31 19:58:38 by ioulkhir		  #+#	#+#			 */
/*   Updated: 2024/12/10 10:22:38 by ioulkhir		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"

char	is_eof(long *new_line_index, char *buffer, long bytes_read)
{
	buffer[bytes_read] = 0;
	*new_line_index = check_new_line(buffer);
	return ((*new_line_index == BUFFER_SIZE - 1)
		|| (*new_line_index == -1 && bytes_read < BUFFER_SIZE));
}

int	precheck_init(int fd,
			long *new_line_index,
			t_data_chunk **head,
			t_data_chunk **curr)
{
	if (fd < 0 || fd >= 1024)
		return (-1);
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (copy_lst_and_free(head, NULL), -1);
	*curr = *head;
	*new_line_index = -1;
	if (*curr != NULL)
		*new_line_index = check_new_line((*curr)->buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_data_chunk		*head;
	t_data_chunk			*curr;
	t_data_chunk			*new_head;
	long					bytes_read;
	long					nl_i;

	if (precheck_init(fd, &nl_i, &head, &curr) == -1)
		return (NULL);
	while (nl_i == -1)
	{
		curr = append_chunk_lst(&head, curr);
		if (curr == NULL)
			return (copy_lst_and_free(&head, NULL), NULL);
		bytes_read = read(fd, curr->buffer, BUFFER_SIZE);
		curr->rest_len = bytes_read;
		if (bytes_read < 0)
			return (copy_lst_and_free(&head, NULL), NULL);
		if (is_eof(&nl_i, curr->buffer, bytes_read))
			return (lst_to_str(&head, curr, bytes_read, NULL));
	}
	new_head = new_chunk();
	if (new_head == NULL)
		return (copy_lst_and_free(&head, NULL), NULL);
	new_head->rest_len = ft_strcpy(curr->buffer + nl_i + 1, new_head->buffer);
	return (lst_to_str(&head, curr, nl_i + 1, new_head));
}

void	copy_lst_and_free(t_data_chunk **head, char *result)
{
	t_data_chunk	*curr;
	t_data_chunk	*tmp;
	long			copied_bytes;

	if (*head == NULL)
		return ;
	copied_bytes = 0;
	if (result)
		copied_bytes += ft_strcpy((*head)->buffer, result);
	curr = (*head)->next;
	1 && (free(*head), *head = NULL);
	while (curr && curr->next)
	{
		if (result)
			copied_bytes += ft_strcpy(curr->buffer, result + copied_bytes);
		1 && (tmp = curr, curr = curr->next);
		free(tmp);
	}
	if (curr)
	{
		result && ft_strcpy(curr->buffer, result + copied_bytes);
		free(curr);
	}
}

char	*lst_to_str(t_data_chunk **head, t_data_chunk *tail
					, long bytes_read, t_data_chunk *new_head)
{
	char			*result;
	long			result_size;

	result_size = calc_result_size(*head, tail, bytes_read, (*head)->lst_size);
	result = malloc((result_size + 1) * sizeof(char));
	copy_lst_and_free(head, result);
	*head = new_head;
	if (!result)
		return (free(new_head), *head = NULL, NULL);
	if (!*result)
		return (free(result), free(new_head), *head = NULL, NULL);
	return (result);
}
