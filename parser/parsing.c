/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-05 09:41:51 by khoukouj          #+#    #+#             */
/*   Updated: 2025-02-05 09:41:51 by khoukouj         ###   ########.1337.ma  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenizer2(t_token	**tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->next)
		{
			if (tmp->type == REDIR_IN)
				tmp->next->type = IN_FILE;
			else if (tmp->type == REDIR_OUT)
				tmp->next->type = OUT_FILE;
			else if (tmp->type == REDIR_APPEND)
				tmp->next->type = A_OUT_FILE;
			else if (tmp->type == HERE_DOC)
				tmp->next->type = DELIMITER;		
		}
		tmp = tmp->next;
	}
	
}

void	tokenizer1(char ** tokens, t_token **toks)
{
	int		i;
	t_token	*token;

	i = -1;
	token = NULL;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "|"))
			token = new_tok_node(tokens[i], PIPE);
		else if (!ft_strcmp(tokens[i], ">>"))
			token = new_tok_node(tokens[i], REDIR_APPEND);
		else if (!ft_strcmp(tokens[i], "<<"))
			token = new_tok_node(tokens[i], HERE_DOC);
		else if (!ft_strcmp(tokens[i], ">"))
			token = new_tok_node(tokens[i], REDIR_OUT);
		else if (!ft_strcmp(tokens[i], "<"))
			token = new_tok_node(tokens[i], REDIR_IN);
		else
			token = new_tok_node(tokens[i], WORD);
		ft_lst_addback(toks, token);
	}
}

int	tokenize(char **tokens, t_token **toks)
{
	tokenizer1(tokens, toks);
	if (syntax_error(*toks))
		return (-1);
	tokenizer2(toks);
	return (0);
}
