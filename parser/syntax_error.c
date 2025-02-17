/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 09:12:20 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-17 09:12:20 by khoukouj         ###   ########.ma       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_unclosed_quotes(char *line, char quote, int *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] && line[*i] == quote)
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	ft_putstr_fd("minishell: syntax error\n", 2);
	return (-1);
}

static int	ft_check_pipe_syntax(char *line, int *i)
{
	(*i)++;
	while (line[*i] && is_whitespace(line[*i]))
		(*i)++;
	if (!line[*i] || line[*i] == '|')
		return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
	return (1);
}

static int	ft_put_redir_syntax_error(char *line, int *i)
{
	if (!line[*i])
		return (ft_putstr_fd("minishell: syntax error\n", 2), -1);
	if (is_redir(line[*i]))
		return (ft_putstr_fd("minishell: syntax error\n", 2), -1);
	if (line[*i] == '|')
		return (ft_putstr_fd("minishell: syntax error\n", 2), -1);
	return (1);
}

static int	ft_check_redir_syntax(char *line, char redir, int *i)
{
	size_t	last;

	last = ft_strlen(line) - 1;
	if (is_redir(line[last]))
		return (ft_putstr_fd("minishell: syntax error\n", 2), -1);
	(*i)++;
	if (line[*i] == redir)
		(*i)++;
	while (line[*i] && is_whitespace(line[*i]))
		(*i)++;
	if (!line[*i] || is_quote(line[*i]))
		return (1);
	return (ft_put_redir_syntax_error(line, i));
}

int	ft_check_syntax_error(char *line)
{
	int	i;

	if (init_syntax_data(&i, line) == -1)
		return (-1);
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			if (ft_check_unclosed_quotes(line, line[i], &i) == -1)
				return (-1);
		}
		else if (line[i] == '|')
		{
			if (ft_check_pipe_syntax(line, &i) == -1)
				return (-1);
		}
		else if (line[i] && is_redir(line[i]))
		{
			if (ft_check_redir_syntax(line, line[i], &i) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (1);
}
