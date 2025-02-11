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

//quotes
int		check_unclosed_quotes(char *line);
int		is_whitespace(char c);
int		strlen_pars(char *s);
char	*trim_line(char *line);
int		quoted(char *str, int index);
int		calc_new_len(char *input);
void	add_spaces(char **input);
char	**str_tokenize(char *line);
int		ft_count_tokens(char *line);
#endif