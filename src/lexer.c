/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:34:45 by lchew             #+#    #+#             */
/*   Updated: 2023/06/10 21:11:00 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	This function will take in a string and return a linked list of tokens.
	The input argument is splitted with ' ' as the delimiter for tokens.
	
	Arguments:
		- cmd: string of commands, options, arguments & operators
	
	Return:
		- The head of linked list of tokens
*/
/* t_lexer	*lexer(char *cmd)
{
	if (!cmd)
		return (NULL);
} */

// static int	op_count(char *cmd)
// {
// 	int		count;

// 	count = 0;
// 	while (*cmd != '\0')
// 	{
// 		if (!ft_strncmp(cmd, PIPE, 1))
// 			++count;
// 		else if (!ft_strncmp(cmd, HEREDOC, 2) || !ft_strncmp(cmd, RDAPP, 2))
// 		{
// 			count += 2;
// 			++cmd;
// 		}
// 		else if (!ft_strncmp(cmd, RDIN, 1) || !ft_strncmp(cmd, RDOUT, 1))
// 			++count;
// 		++cmd;
// 	}
// 	return (count);
// }

static int	token_count(char *cmd)
{
	int		token_count;

	token_count = 0;
	while (*cmd != '\0')
	{
		if (ft_strchr("|<>", *cmd++) != NULL)
		{
			++token_count;
			while (*cmd == *(cmd - 1) && *cmd != '\0')
				++cmd;
		}
		++token_count;
		while (ft_strchr("|<>", *cmd) == NULL && *cmd != '\0')
			++cmd;
	}
	return (token_count);
}

static int	char_count(char const *cmd)
{
	int	count;

	count = 0;
	while (*cmd != '\0' && ft_strchr("|<>", *cmd++) == NULL)
		++count;
	return (count);
}

static int	op_count(char const *cmd)
{
	int	count;

	count = 0;
	if (ft_strchr("|<>", *cmd++) != NULL)
	{
		++count;
		while (*cmd == *(cmd - 1))
		{
			++count;
			++cmd;
		}
	}
	return (count);
}

static char	**cmd_modifier(char *cmd)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = ft_calloc(token_count(cmd) + 1, sizeof(char *));
	i = 0;
	while (*cmd != '\0')
	{
		j = 0;
		if (ft_strchr("|<>", *cmd) != NULL)
		{
			tokens[i] = ft_calloc(op_count(cmd) + 1, sizeof(char));
			tokens[i][j++] = *cmd++;
			while (*cmd == *(cmd - 1))
				tokens[i][j++] = *cmd++;
			tokens[i++][j] = '\0';
		}
		else
		{
			tokens[i] = ft_calloc(char_count(cmd) + 1, sizeof(char));
			while (ft_strchr("|<>", *cmd) == NULL && *cmd != '\0')
				tokens[i][j++] = *cmd++;
			tokens[i++][j] = '\0';
		}
	}
	return (tokens);
}

t_list	*lexer(char *cmd)
{
	char	**tokens;
	char	*tmp;
	t_list	*lexer;
	t_list	*head;

	tokens = cmd_modifier(cmd);
	lexer = ft_lstnew((void *)ft_strdup(*tokens++));
	head = lexer;
	printf("Lexer-list: %s\n", lexer->content);
	while (*tokens != NULL)
	{
		tmp = *tokens;
		*tokens = ft_strtrim(*tokens, " ");
		lexer->next = ft_lstnew((void *)ft_strdup(*tokens));
		lexer = lexer->next;
		printf("Lexer-list: %s\n", lexer->content);
		++tokens;
		free(tmp);
	}
	return (head);
}
