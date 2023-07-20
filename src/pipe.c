/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:06 by lchew             #+#    #+#             */
/*   Updated: 2023/07/20 19:30:16 by lchew            ###   ########.fr       */
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

void	left_child(int	*pipe, t_tree *node, char **envp, t_root *sh)
{
	ft_dup2(pipe[1], STDOUT_FILENO);
	recurse_bst(node->left, envp, sh);
	ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
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
void	right_child(int *pipe, t_tree *node, char **envp, t_root *sh)
{
	ft_dup2(pipe[0], STDIN_FILENO);
	recurse_bst(node->right, envp, sh);
	ft_dup2(sh->stdout_tmp, STDIN_FILENO);
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
void	children(t_tree *node, char **envp, t_root *sh)
{
	pid_t	children[2];
	int		status;
	// int		pipe[2];

	ft_pipe(sh->pipe);
	children[0] = ft_fork();
	if (children[0] == 0)
	{
		left_child(sh->pipe, node, envp, sh);
		exit(0);
	}
	waitpid(children[0], &status, 0);
	ft_close(sh->pipe[1]);
	children[1] = ft_fork();
	if (children[1] == 0)
	{
		right_child(sh->pipe, node, envp, sh);
		exit(0);
	}
	waitpid(children[1], &status, 0);
	ft_close(sh->pipe[0]);
}
