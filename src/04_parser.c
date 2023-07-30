/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:32:06 by lchew             #+#    #+#             */
/*   Updated: 2023/07/30 15:16:28 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tree	*token_check(t_list *lexer, char *op, int n_token, t_root *sh);
static t_token	type_assign(char *value, t_root *sh);

/**
 * parser - Constructs a binary tree from the given list of tokens representing
 *          the command line.
 * @param lexer: The list of tokens.
 * @param n_token: The number of tokens in the list.
 * @param sh: A pointer to the root structure.
 *
 * @returns
 * A pointer to the root of the tree, or NULL if an error occurs or if no tokens
 * are available for parsing.
 */
t_tree	*parser(t_list *lexer, int n_token, t_root *sh)
{
	t_tree	*root;

	root = NULL;
	if (!lexer || n_token <= 0)
		return (NULL);
	root = token_check(lexer, PIPE_OP, n_token, sh);
	if (!root)
		root = token_check(lexer, RDIN_OP, n_token, sh);
	if (!root)
		root = token_check(lexer, RDOUT_OP, n_token, sh);
	if (!root)
		root = token_check(lexer, NULL, n_token, sh);
	return (root);
}

/**
 * token_check - Checks if a specific operator is present in the lexer list and
 *               creates a binary tree node accordingly. Uses a pointer to the
 *               shell's root node to access operator-check structures and
 *               determine the corresponding tree node type.
 * @param lexer: The current position in the list of tokens.
 * @param op: The operator to search for.
 * @param n_token: The number of tokens remaining.
 * @param sh: A pointer to the root structure.
 *
 * @returns
 * A pointer to the new tree node, or NULL if the operator is not found in the
 * lexer list, no operator is provided, or no tokens are available for parsing.
 */
static t_tree	*token_check(t_list *lexer, char *op, int n_token, t_root *sh)
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
	while (lexer != NULL && i < n_token)
	{
		if (!ft_strncmp(lexer->content, op, ft_strlen(op)))
		{
			left = parser(head, i, sh);
			right = parser(lexer->next, n_token - i - 1, sh);
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
static t_token	type_assign(char *value, t_root *sh)
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
