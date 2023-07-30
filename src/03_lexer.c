/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:34:45 by lchew             #+#    #+#             */
/*   Updated: 2023/07/30 14:59:47 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************/

#include "minishell.h"

static void	cmd_modifier(char *cmd, char **tokens);
static void	quote_cmd_mod(char **cmd, char **tokens, int *i, int *j);

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
	int		token_num;
	t_list	*head;
	t_list	*node;

	if (!cmd)
		return (NULL);
	token_num = count_token(cmd);
	if (token_num == -1)
		return (NULL);
	tokens = ft_calloc(token_num + 1, sizeof(char *));
	cmd_modifier(cmd, tokens);
	if (!tokens || !*tokens)
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

/**
 * cmd_modifier - Tokenizes a given command string based on certain characters
 *                ('|', '<', '>').
 * @param cmd: The command string to be tokenized.
 *
 * @returns
 * An array of tokens derived from the command string 'cmd'.
 * Each token can be a command or an operator ('|', '<', '>').
 * This array of tokens is dynamically allocated and hence should be freed
 * by the caller when it is no longer needed. If the command string 'cmd'
 * is empty or NULL, the function returns an array containing a single NULL
 * pointer.
 */
static void	cmd_modifier(char *cmd, char **tokens)
{
	int	i;
	int	j;

	i = 0;
	while (*cmd != '\0')
	{
		j = 0;
		while (*cmd == ' ')
			++cmd;
		if (*cmd == '|')
		{
			tokens[i] = ft_calloc(count_sp_char(cmd) + 1, sizeof(char));
			tokens[i][j++] = *cmd++;
			while (*cmd == *(cmd - 1))
				tokens[i][j++] = *cmd++;
			tokens[i++][j] = '\0';
		}
		else if (ft_strchr("<>", *cmd) != NULL && *cmd != '\0')
		{
			tokens[i] = ft_calloc(count_sp_char(cmd) + 1, sizeof(char));
			tokens[i][j++] = *cmd++;
			while (*cmd == *(cmd - 1) || *cmd == ' ')
				tokens[i][j++] = *cmd++;
			if (ft_strchr("<>", *(cmd - 1)) != NULL && \
				*cmd != ' ' && *cmd != '\0')
				tokens[i][j++] = ' ';
			while (ft_strchr("|<> ", *cmd) == NULL && *cmd != '\0')
				quote_cmd_mod(&cmd, tokens, &i, &j);
			tokens[i][j] = '\0';
			++i;
		}
		else if (*cmd != '\0')
		{
			tokens[i] = ft_calloc(count_char(cmd) + 1, sizeof(char));
			while (ft_strchr("|<>", *cmd) == NULL && *cmd != '\0')
				quote_cmd_mod(&cmd, tokens, &i, &j);
			tokens[i++][j] = '\0';
		}
	}
}

static void	quote_cmd_mod(char **cmd, char **tokens, int *i, int *j)
{
	int	quote_len;

	quote_len = quote_count(*cmd);
	if (quote_len == 0)
	{
		tokens[*i][(*j)++] = **cmd;
		++(*cmd);
	}
	else
	{
		while (quote_len-- > 0)
		{
			tokens[*i][(*j)++] = **cmd;
			++(*cmd);
		}
	}
}
