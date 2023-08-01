/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:59:58 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/01 16:28:24 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tree_transversal(t_tree *node, char **envp, t_root *sh);

void	rdin_handler(t_tree *node, char **envp, t_root *sh)
{
	int	fd;

	fd = 0;
	fd = rdin_fd(node->value, sh);
	if (fd < 0)
		return ;
	ft_dup2(fd, STDIN_FILENO);
	ft_close(fd);
	tree_transversal(node, envp, sh);
}

void	rdout_handler(t_tree *node, char **envp, t_root *sh)
{
	int	fd;

	fd = 0;
	fd = rdout_fd(node->value, sh);
	if (fd < 0)
		return ;
	ft_dup2(fd, STDOUT_FILENO);
	ft_close(fd);
	tree_transversal(node, envp, sh);
}

void	rdapp_handler(t_tree *node, char **envp, t_root *sh)
{
	int	fd;
	int	i;

	i = 0;
	while (node->value[i] == RDOUT_OP[0])
		++i;
	if (i == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (i > 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	if (i > 2)
	{
		g_exit_status = 258;
		return ;
	}
	fd = 0;
	fd = rdapp_fd(node->value, sh);
	if (fd < 0)
		return ;
	ft_dup2(fd, STDOUT_FILENO);
	ft_close(fd);
	tree_transversal(node, envp, sh);
}

void	heredoc_handler(t_tree *node, char **envp, t_root *sh)
{
	int	fd;
	int	i;

	i = 0;
	while (node->value[i] == RDIN_OP[0])
		++i;
	if (i == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (i > 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	if (i > 2)
	{
		g_exit_status = 258;
		return ;
	}
	fd = 0;
	ft_dup2(sh->stdin_tmp, STDIN_FILENO);
	fd = heredoc_fd(node->value, sh);
	if (fd < 0)
		return ;
	if (node->right == NULL || node->right->token != HEREDOC)
		ft_dup2(fd, STDIN_FILENO);
	ft_close(fd);
	tree_transversal(node, envp, sh);
}

/**
 * tree_transversal - Calls the function recurse_bst for the right and left child
 *             of a node if they exist. This function is called when a
 *             redirection token (RDIN or RDOUT) is found in the
 *             binary syntax tree (BST) during traversal by recurse_bst.
 *
 * @param node
 * A pointer to the current node in the BST.
 *
 * @param envp
 * The current environment variables.
 *
 * @returns
 * Void.
 */
static void	tree_transversal(t_tree *node, char **envp, t_root *sh)
{
	if (node->right != NULL)
	{
		if (node->left != NULL && node->left->token == COMMAND && \
			node->right->token == COMMAND)
			sh->tree_arg_value = node->right->value;
		else
			recurse_bst(node->right, envp, sh);
	}
	if (node->left != NULL)
		recurse_bst(node->left, envp, sh);
}
