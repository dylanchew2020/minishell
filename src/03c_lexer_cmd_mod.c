/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03c_lexer_cmd_mod.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:51:30 by lchew             #+#    #+#             */
/*   Updated: 2023/08/01 16:29:13 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_cmd_mod(char **cmd, char **tokens, int *i, int *j);
static void	pipe_tokenize(char **cmd, char **tokens, int *i, int *j);
static void	redir_tokenize(char **cmd, char **tokens, int *i, int *j);

void	cmd_modifier(char *cmd, char **tokens)
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
			pipe_tokenize(&cmd, tokens, &i, &j);
		else if (ft_strchr("<>", *cmd) != NULL && *cmd != '\0')
			redir_tokenize(&cmd, tokens, &i, &j);
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

static void	pipe_tokenize(char **cmd, char **tokens, int *i, int *j)
{
	tokens[*i] = ft_calloc(count_sp_char(*cmd) + 1, sizeof(char));
	tokens[*i][(*j)++] = **cmd;
	++(*cmd);
	while (**cmd == *(*cmd - 1))
	{
		tokens[*i][(*j)++] = **cmd;
		++(*cmd);
	}
	tokens[(*i)++][*j] = '\0';
}

static void	redir_tokenize(char **cmd, char **tokens, int *i, int *j)
{
	tokens[*i] = ft_calloc(count_sp_char(*cmd) + 1, sizeof(char));
	tokens[*i][(*j)++] = **cmd;
	++(*cmd);
	while (**cmd == *(*cmd - 1) || **cmd == ' ')
	{
		tokens[*i][(*j)++] = **cmd;
		++(*cmd);
	}
	if (ft_strchr("<>", *(*cmd - 1)) != NULL && **cmd != ' ' && **cmd != '\0')
		tokens[*i][(*j)++] = ' ';
	while (ft_strchr("|<> ", **cmd) == NULL && **cmd != '\0')
		quote_cmd_mod(cmd, tokens, i, j);
	tokens[*i][*j] = '\0';
	++(*i);
}
