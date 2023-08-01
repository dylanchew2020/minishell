/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:34:45 by lchew             #+#    #+#             */
/*   Updated: 2023/08/01 19:51:32 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************/

#include "minishell.h"

static char	**tokenizer(char *cmd);

/**
 * lexer - Converts a command string into a list of tokens, where a token can
 *         be either a command or an operator ('|', '<', '>').
 *         It trims leading and trailing spaces from each token.
 * @param cmd: The command string to tokenize.
 *
 * @returns
 * A linked list where each node holds a token from the command string,
 * or NULL if there's an error during the process.
 */
t_list	*lexer(char *cmd)
{
	char	**tokens;
	char	**tokens_head;
	t_list	*head;
	t_list	*node;

	tokens = tokenizer(cmd);
	if (!tokens)
		return (NULL);
	tokens_head = tokens;
	head = ft_lstnew(ft_strtrim(*tokens++, " "));
	if (!head)
		return (NULL);
	node = head;
	while (*tokens)
	{
		node->next = ft_lstnew(ft_strtrim(*tokens++, " "));
		if (!(node->next))
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		node = node->next;
	}
	free_2d(tokens_head);
	return (head);
}

static char	**tokenizer(char *cmd)
{
	int		token_num;
	char	**tokens;

	if (!cmd)
		return (NULL);
	if (!(*cmd))
	{
		free(cmd);
		return (NULL);
	}
	token_num = count_token(cmd);
	if (token_num == -1)
	{
		free(cmd);
		return (NULL);
	}
	tokens = ft_calloc(token_num + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	cmd_modifier(cmd, tokens);
	if (!tokens || !*tokens)
		return (NULL);
	return (tokens);
}
