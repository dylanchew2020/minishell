/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:32:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/06 16:31:53 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*tree_node_new(t_token token, char *value, t_tree *left, t_tree *right)
{
	t_tree	*tree;

	tree = ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->token = token;
	tree->value = ft_strdup(value);
	tree->left = left;
	tree->right = right;
	return (tree);
}

/* 
	EG
	ls -l | grep test | cat > output
 */
t_tree	*op_check(t_list *lexer, char op, int num_tokens, int redirect)
{
	t_tree	*node;
	t_tree	*left;
	t_tree	*right;
	t_list	*head;
	int		i;

	i = 0;
	head = lexer;
	while (lexer != NULL && i < num_tokens)
	{
		if (*(char *)(lexer->content) == op)
		{
			left = parser(head, i, redirect);
			if (op == REDIRECT_OUT || op == REDIRECT_IN)
				redirect = 1;
			right = parser(lexer->next, num_tokens - i - 1, redirect);
			node = tree_node_new(OPERATOR, lexer->content, left, right);
			return (node);
		}
		lexer = lexer->next;
		++i;
	}
	return (NULL);
}

t_tree	*cmd_check(t_list *lexer, int num_tokens, int redirect)
{
	t_tree	*node;
	char	*cmd;
	char	*tmp;

	if (!lexer)
		return (NULL);
	cmd = ft_strdup(lexer->content);
	lexer = lexer->next;
	while (num_tokens > 0 && lexer != NULL)
	{
		tmp = cmd;
		cmd = ft_strjoin(cmd, lexer->content);
		free(tmp);
		lexer = lexer->next;
	}
	node = tree_node_new(COMMAND, cmd, NULL, NULL);
	/* option = NULL;
	arg = NULL;
	head = lexer;
	lexer = lexer->next;
	while (num_tokens-- > 1 && lexer != NULL)
	{
		if (ft_strncmp(lexer->content, "-", 1) == 0)
			option = tree_node_new(OPTION, lexer->content, NULL, NULL);
		else if (ft_strncmp(lexer->content, "-", 1) != 0)
			arg = tree_node_new(ARGUMENT, lexer->content, NULL, NULL);
		lexer = lexer->next;
	}
	if (redirect == 1)
		cmd = tree_node_new(ARGUMENT, head->content, option, arg);
	else
		cmd = tree_node_new(COMMAND, head->content, option, arg); */
	return (node);
}

t_tree	*parser(t_list *lexer, int num_tokens, int redirect)
{
	t_tree	*root;

	root = NULL;
	if (!lexer)
		return (NULL);
	root = op_check(lexer, PIPE, num_tokens, redirect);
	if (!root)
		root = op_check(lexer, REDIRECT_OUT, num_tokens, redirect);
	if (!root)
		root = op_check(lexer, REDIRECT_IN, num_tokens, redirect);
	if (!root)
		root = cmd_check(lexer, num_tokens, redirect);
	return (root);
}
