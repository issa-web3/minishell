/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-10 10:26:19 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-10 10:26:19 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_spaces_redir(char *input, char *new_input, int *i, int *j)
{
	if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
	{
		if (*i > 0 && !is_whitespace(input[*i - 1]))
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		new_input[(*j)++] = input[*i];
		if (input[*i + 1] && !is_whitespace(input[*i + 1]))
			new_input[(*j)++] = ' ';
	}
	else
	{
		if (*i > 0 && !is_whitespace(input[*i - 1]))
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[*i];
		if (input[*i + 1] && !is_whitespace(input[*i + 1]))
			new_input[(*j)++] = ' ';
	}
}

void	add_spaces_pipes(char *input, char *new_input, int *i, int *j)
{
	if (input[*i] == '|' && !quoted(input, *i))
	{
		if (*i > 0 && !is_whitespace(input[*i - 1]))
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[*i];
		if (input[*i + 1] && !is_whitespace(input[*i + 1]))
			new_input[(*j)++] = ' ';
	}
	else
		new_input[(*j)++] = input[*i];
}

void	add_spaces(char **input)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_input;
	char	*tmp;

	i = -1;
	new_len = calc_new_len(*input);
	new_input = malloc(new_len + 1);
	if (!new_input)
		return ;
	j = 0;
	while ((*input)[++i])
	{
		if (((*input)[i] == '>' || (*input)[i] == '<') && !quoted(*input, i))
			add_spaces_redir(*input, new_input, &i, &j);
		else
			add_spaces_pipes(*input, new_input, &i, &j);
	}
	new_input[j] = '\0';
	tmp = *input;
	*input = new_input;
	free(tmp);
}
