/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:28:23 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/30 15:15:59 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_tree(t_tree *root, int b)
{
	static int	level;

	if (b == 0)
		++level;
	if (root == NULL)
	{
		printf("NULL\n");
		if (b == 0)
			--level;
		return ;
	}
	printf("token (%u): (%s)\n", root->token, root->value);
	printf("left %i  ", level);
	print_tree(root->left, 0);
	printf("right %i  ", level);
	print_tree(root->right, 0);
	--level;
}
