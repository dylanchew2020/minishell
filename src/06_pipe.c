/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:06 by lchew             #+#    #+#             */
/*   Updated: 2023/07/30 15:35:13 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_heredoc(t_tree *node, char **envp, t_root *sh);
static void	pipe_child_process(t_tree *node, char **envp, t_root *sh);

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
void	pipe_handler(t_tree *node, char **envp, t_root *sh)
{
	if (node->left == NULL)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	if (node->right == NULL)
	{
		printf("minishell: syntax error: unexpected end of file\n");
		return ;
	}
	ft_pipe(sh->pipe);
	pipe_heredoc(node, envp, sh);
	pipe_child_process(node, envp, sh);
}

static void	pipe_heredoc(t_tree *node, char **envp, t_root *sh)
{
	if (node->left->token == HEREDOC)
	{
		ft_dup2(sh->pipe[1], STDOUT_FILENO);
		recurse_bst(node->left, envp, sh);
		ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
	}
	if (node->right->token == HEREDOC)
	{
		ft_dup2(sh->pipe[0], STDIN_FILENO);
		recurse_bst(node->right, envp, sh);
		ft_dup2(sh->stdin_tmp, STDIN_FILENO);
	}
}

static void	left_child(int	*pipe, t_tree *node, char **envp, t_root *sh);
static void	right_child(int *pipe, t_tree *node, char **envp, t_root *sh);

static void	pipe_child_process(t_tree *node, char **envp, t_root *sh)
{
	pid_t	children[2];

	children[0] = ft_fork();
	if (children[0] == 0)
	{
		if (node->left->token != HEREDOC)
			left_child(sh->pipe, node, envp, sh);
		exit(EXIT_SUCCESS);
	}
	children[1] = ft_fork();
	if (children[1] == 0)
	{
		if (node->right->token != HEREDOC)
			right_child(sh->pipe, node, envp, sh);
		exit(EXIT_SUCCESS);
	}
	ft_close(sh->pipe[1]);
	ft_close(sh->pipe[0]);
	sh->pipe[1] = 0;
	sh->pipe[0] = 0;
	waitpid(children[0], &g_exit_status, 0);
	waitpid(children[1], &g_exit_status, 0);
	g_exit_status = exit_status(g_exit_status);
}

/**
 * left_child - Handles the left child process in a binary syntax tree
 * 				(BST) traversal, redirecting STDOUT to the pipe WRITE-end and
 * 				recursively processing the left child node.
 *
 * @param data: A pointer to the pipe data structure.
 * @param node: A pointer to the current node in the BST.
 * @param envp: The current environment variables.
 *
 * @returns void.
 */

static void	left_child(int	*pipe, t_tree *node, char **envp, t_root *sh)
{
	ft_dup2(pipe[1], STDOUT_FILENO);
	ft_close(sh->pipe[0]);
	sh->pipe[0] = 0;
	recurse_bst(node->left, envp, sh);
	ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
}

/**
 * right_child - Handles the right child process in a binary syntax
 * 				 tree (BST) traversal, redirecting STDIN to the
 * 				 pipe READ-end and recursively processing the right
 * 				 child node.
 *
 * @param data: A pointer to the pipe data structure.
 * @param node: A pointer to the current node in the BST.
 * @param envp: The current environment variables.
 *
 * @returns void.
 */
static void	right_child(int *pipe, t_tree *node, char **envp, t_root *sh)
{
	ft_dup2(pipe[0], STDIN_FILENO);
	ft_close(sh->pipe[1]);
	sh->pipe[1] = 0;
	recurse_bst(node->right, envp, sh);
	ft_dup2(sh->stdin_tmp, STDIN_FILENO);
}
