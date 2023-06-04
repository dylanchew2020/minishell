/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:32:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/04 22:52:29 by lchew            ###   ########.fr       */
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
t_tree	*op_check(t_list *lexer, char op, int num_tokens)
{
	t_tree	*root;
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
			left = parser(head, i);
			right = parser(lexer->next, num_tokens - i - 1);
			root = tree_node_new(OPERATOR, lexer->content, left, right);
			return (root);
		}
		lexer = lexer->next;
		++i;
	}
	return (NULL);
}

t_tree	*cmd_check(t_list *lexer, int num_tokens)
{
	t_tree	*root;

	if (!lexer)
		return (NULL);
	if (lexer->content == EXIT || lexer->content == CD || lexer->content == PWD
		|| lexer->content == EXPORT || lexer->content == UNSET
		|| lexer->content == ENV || lexer->content == ECHO)
		root = tree_node_new(COMMAND, lexer->content, NULL, NULL);
	else if (*(char *)(lexer->content) == '-')
		root = tree_node_new(OPTION, lexer->content, NULL, NULL);
	else
		root = tree_node_new(ARGUMENT, lexer->content, NULL, NULL);
	return (root);
}

t_tree	*parser(t_list *lexer, int num_tokens)
{
	t_tree	*root;

	if (!lexer)
		return (NULL);
	op_check(lexer, PIPE, num_tokens);
	op_check(lexer, REDIRECT_IN, num_tokens);
	op_check(lexer, REDIRECT_OUT, num_tokens);
	cmd_check(lexer, num_tokens);
	return (root);
}