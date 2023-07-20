/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:32:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/14 23:18:00 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * parser - Constructs a binary tree from the given list of tokens representing
 *          the command line.
 * @param lexer: The list of tokens.
 * @param num_tokens: The number of tokens in the list.
 * @param sh: A pointer to the root structure.
 *
 * @returns
 * A pointer to the root of the tree, or NULL if an error occurs or if no tokens
 * are available for parsing.
 */
t_tree	*parser(t_list *lexer, int num_tokens, t_root *sh)
{
	t_tree	*root;

	root = NULL;
	if (!lexer || num_tokens <= 0)
		return (NULL);
	root = token_check(lexer, PIPE_OP, num_tokens, sh);
	if (!root)
		root = token_check(lexer, RDIN_OP, num_tokens, sh);
	if (!root)
		root = token_check(lexer, RDOUT_OP, num_tokens, sh);
	if (!root)
		root = token_check(lexer, NULL, num_tokens, sh);
	return (root);
}

/**
 * token_check - Checks if a specific operator is present in the lexer list and
 *               creates a binary tree node accordingly. Uses a pointer to the
 *               shell's root node to access operator-check structures and
 *               determine the corresponding tree node type.
 * @param lexer: The current position in the list of tokens.
 * @param op: The operator to search for.
 * @param num_tokens: The number of tokens remaining.
 * @param sh: A pointer to the root structure.
 *
 * @returns
 * A pointer to the new tree node, or NULL if the operator is not found in the
 * lexer list, no operator is provided, or no tokens are available for parsing.
 */
t_tree	*token_check(t_list *lexer, char *op, int num_tokens, t_root *sh)
{
	t_tree	*left;
	t_tree	*right;
	t_list	*head;
	t_token	type;
	int		i;

	i = 0;
	head = lexer;
	if (op == NULL)
		return (tree_node_new(COMMAND, lexer->content, NULL, NULL));
	while (lexer != NULL && i < num_tokens)
	{
		if (!ft_strncmp(lexer->content, op, ft_strlen(op)))
		{
			left = parser(head, i, sh);
			right = parser(lexer->next, num_tokens - i - 1, sh);
			type = type_assign(lexer->content, sh);
			return (tree_node_new(type, lexer->content, left, right));
		}
		lexer = lexer->next;
		++i;
	}
	return (NULL);
}

/**
 * type_assign - Determines the token type based on the string value, using
 *               operator-check structures in the shell's root structure.
 * @param value: The string value to check.
 * @param left: The left child of the potential node (unused in this function,
 *              included for completeness).
 * @param right: The right child of the potential node (unused in this function,
 *               included for completeness).
 * @param sh: A pointer to the root structure.
 *
 * @returns
 * The token type corresponding to the string value, or END if the value does
 * not match any operator in the shell's operator-check structures.
 */
t_token	type_assign(char *value, t_root *sh)
{
	int				j;

	j = 0;
	while (sh->tkchk[j].op != NULL)
	{
		if (!ft_strncmp(value, sh->tkchk[j].op, ft_strlen(sh->tkchk[j].op)))
			return (sh->tkchk[j].token);
		++j;
	}
	return (END);
}

/**
 * tree_node_new - Allocates memory for and initializes a new binary tree node.
 * @param type: The token type the new node will hold.
 * @param value: The string value the new node will hold.
 * @param left: A pointer to the new node's left child.
 * @param right: A pointer to the new node's right child.
 *
 * @returns
 * A pointer to the newly created tree node, or NULL if memory allocation fails.
 */
t_tree	*tree_node_new(t_token type, char *value, t_tree *left, t_tree *right)
{
	t_tree	*tree;

	tree = ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->token = type;
	tree->value = value;
	tree->left = left;
	tree->right = right;
	return (tree);
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
// t_tree	*op_check(t_list *lexer, char *op, int num_tokens)
// {
// 	t_tree	*left;
// 	t_tree	*right;
// 	t_list	*head;
// 	int		i;

// 	i = 0;
// 	head = lexer;
// 	if (op == NULL)
// 		return (tree_node_new(COMMAND, lexer->content, NULL, NULL));
// 	while (lexer != NULL && i < num_tokens)
// 	{
// 		if (!ft_strncmp(lexer->content, op, ft_strlen(op)))
// 		{
// 			left = parser(head, i);
// 			right = parser(lexer->next, num_tokens - i - 1);
// 			if (!ft_strncmp(lexer->content, RDAPP, ft_strlen(RDAPP)))
// 				return (tree_node_new(RDAPP_OP, lexer->content, left, right));
// 			else if (!ft_strncmp(lexer->content, HEREDOC, ft_strlen(HEREDOC)))
// 				return (tree_node_new(HEREDOC_OP, lexer->content, left, right));
// 			else if (!ft_strncmp(lexer->content, RDIN, ft_strlen(RDIN)))
// 				return (tree_node_new(RDIN_OP, lexer->content, left, right));
// 			else if (!ft_strncmp(lexer->content, RDOUT, ft_strlen(RDOUT)))
// 				return (tree_node_new(RDOUT_OP, lexer->content, left, right));
// 			else if (!ft_strncmp(lexer->content, PIPE, ft_strlen(PIPE)))
// 				return (tree_node_new(PIPE_OP, lexer->content, left, right));
// 		}
// 		lexer = lexer->next;
// 		++i;
// 	}
// 	return (NULL);
// }

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
// t_tree	*cmd_check(t_list *lexer, int num_tokens)
// {
// 	t_tree	*node;

// 	if (!lexer)
// 		return (NULL);
// 	node = tree_node_new(COMMAND, lexer->content, NULL, NULL);
// 	return (node);
// }
