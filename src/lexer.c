/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:34:45 by lchew             #+#    #+#             */
/*   Updated: 2023/06/28 18:42:18 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_modifier(char *cmd, char **tokens);
static int	token_count(char *cmd);
static int	sp_count(char *cmd);
static int	char_count(char *cmd);
static void	quote_char_mod(char **cmd, int *count);

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
	int		*value_len;
	t_list	*head;
	t_list	*node;

	if (!cmd)
		return (NULL);
	token_num = token_count(cmd);
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
	// printf("node->content: %s\n", node->content);
	while (*tokens)
	{
		node->next = ft_lstnew(ft_strtrim(*tokens++, " "));
		if (!(node->next))
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		node = node->next;
		// printf("node->content: %s\n", node->content);
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
	int	quote_len;

	i = 0;
	while (*cmd != '\0')
	{
		j = 0;
		while (*cmd == ' ')
			++cmd;
		if (ft_strchr("|", *cmd) != NULL && *cmd != '\0')
		{
			tokens[i] = ft_calloc(sp_count(cmd) + 1, sizeof(char));
			tokens[i][j++] = *cmd++;
			while (*cmd == *(cmd - 1))
				tokens[i][j++] = *cmd++;
			tokens[i++][j] = '\0';
		}
		else if (ft_strchr("<>", *cmd) != NULL && *cmd != '\0')
		{
			printf("sp_count|%d\n", sp_count(cmd));
			tokens[i] = ft_calloc(sp_count(cmd) + 1, sizeof(char));
			tokens[i][j++] = *cmd++;
			while (*cmd == *(cmd - 1) || *cmd == ' ')
				tokens[i][j++] = *cmd++;
			if (ft_strchr("<>", *(cmd - 1)) != NULL && *cmd != ' ' && *cmd != '\0')
				tokens[i][j++] = ' ';
			while (ft_strchr("|<> ", *cmd) == NULL && *cmd != '\0')
			{
				quote_len = quote_count(cmd) + 1;
				if (quote_len == 1)
					tokens[i][j++] = *cmd++;
				else
				{
					while (quote_len-- > 0)
						tokens[i][j++] = *cmd++;
				}
			}
			tokens[i][j] = '\0';
			++i;
		}
		else if (*cmd != '\0')
		{
			tokens[i] = ft_calloc(char_count(cmd) + 1, sizeof(char));
			while (ft_strchr("|<>", *cmd) == NULL && *cmd != '\0')
			{
				quote_len = quote_count(cmd) + 1;
				if (quote_len == 1)
					tokens[i][j++] = *cmd++;
				else
				{
					while (quote_len-- > 0)
						tokens[i][j++] = *cmd++;
				}
			}
			tokens[i++][j] = '\0';
		}
	}
}

/**
 * token_count - Counts the number of tokens in a command string, where a token
 *               can be either a command or an operator ('|', '<', '>').
 * @param cmd: The command string to count tokens in.
 *
 * @returns
 * The number of tokens in the command string.
 * A token is either a command (a sequence of non-special characters)
 * or an operator (a sequence of consecutive identical special characters).
 */
static int	token_count(char *cmd)
{
	int	token_count;
	int	quote_len;

	token_count = 0;
	quote_len = 0;
	while (*cmd != '\0')
	{
		while (*cmd == ' ')
				++cmd;
		if (*cmd == '|')
		{
			while (*cmd == '|')
				++cmd;
			++token_count;
		}
		else if (*cmd != '\0' && ft_strchr("<>", *cmd) != NULL)
		{
			++cmd;
			while (*cmd == *(cmd - 1) || *cmd == ' ')
				++cmd;
			while (*cmd != '\0' && ft_strchr("|<> ", *cmd) == NULL)
			{
				quote_len = quote_count(cmd++);
				if (quote_len == -1)
					return (-1);
				cmd += quote_len;
			}
			++token_count;
		}
		else
		{
			while (*cmd != '\0' && ft_strchr("|<>", *cmd) == NULL)
			{
				quote_len = quote_count(cmd++);
				if (quote_len == -1)
					return (-1);
				cmd += quote_len;
			}
			++token_count;
		}
	}
	return (token_count);
}

/**
 * char_count - Counts the number of consecutive identical special or
 *               non-special characters at the beginning of a string based
 *               on the 'special' parameter.
 * @param cmd: The string in which to count characters.
 * @param special: If 1, the function counts consecutive identical special
 *                 characters (i.e., '|', '<', '>'). If 0, it counts consecutive
 *                 non-special characters.
 *
 * @returns
 * The number of consecutive identical characters at the beginning of the string
 * that match the 'special' criterion.
 */
static int	sp_count(char *cmd)
{
	int	count;

	count = 0;
	if (*cmd == '|')
	{
		while (*cmd == '|')
		{
			++count;
			++cmd;
		}
	}
	else if (*cmd != '\0' && ft_strchr("<>", *cmd++) != NULL)
	{
		++count;
		while (*cmd == *(cmd - 1) || *cmd == ' ')
		{
			++count;
			++cmd;
		}
		if (ft_strchr("<>", *(cmd - 1)) != NULL && *cmd != ' ' && *cmd != '\0')
			++count;
		while (*cmd != '\0' && ft_strchr("|<> ", *cmd) == NULL)
			quote_char_mod(&cmd, &count);
	}
	return (count);
}

static int	char_count(char *cmd)
{
	int	count;
	int	quote_len;

	count = 0;
	while (ft_strchr("|<>", *cmd) == NULL && *cmd != '\0')
		quote_char_mod(&cmd, &count);
	return (count);
}

static void quote_char_mod(char **cmd, int *count)
{
	int	quote_len;

	quote_len = quote_count(*cmd) + 1;
	if (quote_len == 1)
	{
		++(*count);
		++(*cmd);
	}
	else
	{
		while (quote_len-- > 0)
		{
			++(*count);
			++(*cmd);
		}
	}
}