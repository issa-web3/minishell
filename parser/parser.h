/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:59:53 by khoukouj          #+#    #+#             */
/*   Updated: 2025/02/05 13:12:02 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
// inc
# include "../minishell.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	APPEND,
	REDIR_INPUT,
	REDIR_OUTPUT,
	HERE_DOC,
}	t_token_type;

//utils
int			is_whitespace(char c);
int			is_redir(char c);
int			is_quote(char c);
int			init_syntax_data(int *i, char *line);
int			is_operator(char c);
void		ft_skip_quotes(char *str, int *i);
char		*ft_strtrim(char *str, char *set, t_garbage **to_free);
char		*ft_strldup(char *str, size_t len, t_garbage **garbage);
void		ft_append_to_lst(t_token **lst, t_token *node);
void		ft_lstadd_back_t2exec(t_2_exec **lst, t_2_exec *new);
//syntax error
int			ft_check_syntax_error(char *line);
// tokens
t_token		*ft_create_tokens(char *str, t_garbage **garbage);
void		ft_handle_cmd(t_2_exec **node, t_garbage **garbage, t_token **tokens);
t_2_exec	*ft_analyse(char *line, t_garbage **garbage);
char		**extract(char **old_str, char *new, t_garbage **garbage);
#endif