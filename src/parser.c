/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:32:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/14 15:51:08 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * parser - Parses the list of tokens and constructs a binary tree 
 *          representation of the command line.
 * @param lexer: The list of tokens.
 * @param num_tokens: The number of tokens in the list.
 * @param redirect: Indicates if the next token is a file argument for 
 * 					redirection.
 *
 * @returns 
 * A pointer to the root of the tree, or NULL if an error occurs.
 */
t_tree	*parser(t_list *lexer, int num_tokens)
{
	t_tree	*root;
	int		nt;

	root = NULL;
	if (!lexer || num_tokens <= 0)
		return (NULL);
	root = op_check(lexer, PIPE, num_tokens);
	if (!root)
		root = op_check(lexer, RDOUT, num_tokens);
	if (!root)
		root = op_check(lexer, RDIN, num_tokens);
	if (!root)
		root = op_check(lexer, NULL, num_tokens);
	return (root);
}

/**
 * op_check - Searches for a specific operator in the lexer list and creates 
 *            a tree node with left and right children when the operator is 
 *            found.
 * @param lexer: The current position in the list of tokens.
 * @param op: The operator to search for.
 * @param num_tokens: The number of tokens remaining.
 * @param redirect: Indicates if the next token is a file argument for 
 *                  redirection.
 *
 * @returns 
 * A pointer to the new node, or NULL if the operator is not found in the 
 * lexer list.
 */
t_tree	*op_check(t_list *lexer, char *op, int num_tokens)
{
	t_tree	*left;
	t_tree	*right;
	t_list	*head;
	int		i;

	i = 0;
	head = lexer;
	if (op == NULL)
		return (tree_node_new(COMMAND, lexer->content, NULL, NULL));
	while (lexer != NULL && i < num_tokens)
	{
		if (!ft_strncmp(lexer->content, op, ft_strlen(op)))
		{
			left = parser(head, i);
			right = parser(lexer->next, num_tokens - i - 1);
			if (!ft_strncmp(lexer->content, RDIN, ft_strlen(RDIN)))
				return (tree_node_new(RDIN_OP, lexer->content, left, right));
			else if (!ft_strncmp(lexer->content, RDOUT, ft_strlen(RDOUT)))
				return (tree_node_new(RDOUT_OP, lexer->content, left, right));
			else if (!ft_strncmp(lexer->content, RDAPP, ft_strlen(RDAPP)))
				return (tree_node_new(RDAPP_OP, lexer->content, left, right));
			else if (!ft_strncmp(lexer->content, HEREDOC, ft_strlen(HEREDOC)))
				return (tree_node_new(HEREDOC_OP, lexer->content, left, right));
			else if (!ft_strncmp(lexer->content, PIPE, ft_strlen(PIPE)))
				return (tree_node_new(PIPE_OP, lexer->content, left, right));
		}
		lexer = lexer->next;
		++i;
	}
	return (NULL);
}

/**
 * cmd_check - Creates a new tree node if the lexer at the current position 
 *             is not a redirection operator.
 * @param lexer: The current position in the list of tokens.
 * @param num_tokens: The number of tokens remaining.
 * @param redirect: Indicates if the next token is a file argument for 
 *                  redirection.
 *
 * @returns 
 * A pointer to the new node, or NULL if lexer is NULL or a redirection operator.
 */
t_tree	*cmd_check(t_list *lexer, int num_tokens)
{
	t_tree	*node;

	if (!lexer)
		return (NULL);
	node = tree_node_new(COMMAND, lexer->content, NULL, NULL);
	return (node);
}

/**
 * tree_node_new - Creates a new binary tree node.
 * @param token: The type of token the node will hold.
 * @param value: The string value the node will hold.
 * @param left: The left child of the node.
 * @param right: The right child of the node.
 *
 * @returns 
 * A pointer to the new node, or NULL if memory allocation fails.
 */
t_tree	*tree_node_new(t_token token, char *value, t_tree *left, t_tree *right)
{
	t_tree	*tree;

	tree = ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->token = token;
	tree->value = value;
	tree->left = left;
	tree->right = right;
	return (tree);
}
