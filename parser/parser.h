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
	OUT_FILE,
	IN_FILE,
	APPEND_FILE,
}	t_token_type;

//utils
int			is_whitespace(char c);
int			is_redir(char c);
int			is_valid_var(int c);
int			is_quote(char c);
int			init_syntax_data(int *i, char *line);
int			is_operator(char c);
void		ft_skip_quoted_section(char *str, int *i, char quote_type);
char		*ft_strtrim(char *str, char *set, t_garbage **to_free);
char		*ft_strldup(char *str, size_t len, t_garbage **garbage);
void		ft_append_to_lst(t_token **lst, t_token *node);
void		ft_lstadd_back_t2exec(t_2_exec **lst, t_2_exec *new);
void		ft_lstadd_back_t_file(t_file **lst, t_file *new);
int			can_i_expand(char *str);
int			my_count_words(const char *str);
void		check_export(t_token **node, int *is_export);
//syntax error
int			ft_check_syntax_error(char *line);
// tokens
t_token		*ft_create_tokens(char *str, t_env *env, t_garbage **garbage);
void		ft_handle_cmd(t_2_exec **node, t_garbage **garbage, t_token **tokens);
t_2_exec	*ft_analyse(char *line, t_env *envl, t_garbage **garbage);
char		**extract(char **old_str, char *new, t_garbage **garbage);
char		*ft_replace_dollar(char *str, t_env *env, t_garbage **garbage);
t_token		*remove_quotes_from_toks(t_token *toks, t_garbage **g);
char		**ft_strtok(char *s, t_garbage **my_garbage);
t_token		*ft_lstlast_token(t_token *lst);
t_token		*new_token_node(char *str, int type, int expanded, t_garbage **garbage);
void		to_expand(t_token **node, t_env *env, t_garbage **g);
//expanding
void		ft_expand_token(t_token **node, t_env *envl, t_garbage **garbage);
t_expand	*ft_create_expand_node(char *s, t_garbage **garbage);
void		ft_lstadd_back_t_expand(t_expand **lst, t_expand *new);
#endif