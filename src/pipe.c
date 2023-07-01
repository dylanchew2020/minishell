/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/28 19:32:25 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * left_child - Handles the left child process in a binary syntax tree 
 * 				(BST) traversal, redirecting STDOUT to the pipe and 
 * 				recursively processing the left child node.
 *
 * @param data: A pointer to the pipe data structure.
 * @param node: A pointer to the current node in the BST.
 * @param envp: The current environment variables.
 *
 * @returns void.
 */

void	left_child(t_pipe *data, t_tree *node, char **envp)
{
	dup2(data->p[1], 1);
	ft_close(data->p[1]);
	ft_close(data->p[0]);
	recurse_bst(node->left, envp);
}

/**
 * right_child - Handles the right child process in a binary syntax 
 * 				 tree (BST) traversal, redirecting STDIN to the 
 * 				 pipe and recursively processing the right
 * 				 child node.
 *
 * @param data: A pointer to the pipe data structure.
 * @param node: A pointer to the current node in the BST.
 * @param envp: The current environment variables.
 *
 * @returns void.
 */
void	right_child(t_pipe *data, t_tree *node, char **envp)
{
	dup2(data->p[0], 0);
	ft_close(data->p[0]);
	ft_close(data->p[1]);
	recurse_bst(node->right, envp);
}

/**
 * children - Handles the child processes in a binary syntax tree (BST)
 *            traversal, creating pipes, forking child processes, and 
 *            waiting for them to complete.
 *
 * @param node: A pointer to the current node in the BST.
 * @param envp: The current environment variables.
 *
 * @returns void.
 */
void	children(t_tree *node, char **envp)
{
	t_pipe	*data;
	pid_t	children[2];
	int		status;

	data = ft_calloc(1, sizeof(t_pipe));
	ft_pipe(data->p);
	children[0] = ft_fork();
	if (children[0] == 0)
	{
		left_child(data, node, envp);
		exit(0);
	}
	children[1] = ft_fork();
	if (children[1] == 0)
	{
		right_child(data, node, envp);
		exit(0);
	}
	ft_close(data->p[0]);
	ft_close(data->p[1]);
	waitpid(-1, &status, 0);
	free(data);
}
