/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:08 by lchew             #+#    #+#             */
/*   Updated: 2023/07/29 15:54:37 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * recurse_bst - Traverses a binary syntax tree (BST) recursively, processing
 *               each node based on its token type. When a PIPE token is found,
 *               it forks new processes. When RDIN or RDOUT tokens are found,
 *               it changes the file descriptor of STDIN or STDOUT respectively,
 *               then handles redirection arguments. When a COMMAND token is
 *               found, it executes the command.
 *
 * @param node: A pointer to the current node in the BST.
 * @param envp: The current environment variables.
 *
 * @returns
 * Void.
 */
void	recurse_bst(t_tree *node, char **envp, t_root *sh)
{
	if (node == NULL)
		return ;
	if (node->token == PIPE)
		children(node, envp, sh);
	else if (node->token == RDIN)
		recurse_rdin(node, envp, sh);
	else if (node->token == RDOUT)
		recurse_rdout(node, envp, sh);
	else if (node->token == RDAPP)
		recurse_rdapp(node, envp, sh);
	else if (node->token == HEREDOC)
		recurse_heredoc(node, envp, sh);
	else if (node->token == COMMAND)
		exec_cmd(node->value, envp, sh);
}

/**
 * redir_arg - Calls the function recurse_bst for the right and left child
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
void	redir_arg(t_tree *node, char **envp, t_root *sh)
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

/**
 * exec_cmd - Executes a command by searching for its path, forking a
 * 			  child process, and using execve to run the command in the
 * 			  child process.
 *
 * @param argv: A string containing the command to be executed.
 * @param envp: The current environment variables.
 *
 * @returns
 *  void.
 */
void	exec_cmd(char *argv, char **envp, t_root *sh)
{
	char	*path;
	char	**cmd;
	pid_t	child;
	int		status;

	if (ft_strncmp(argv, "history", 7) == 0)
		return (history_print(sh->history));
	cmd = cmd_quote_handler(argv, ' ');
	if (sh->tree_arg_value != NULL)
		cmd = cmd_join(cmd, sh);
	print_exec_cmd(cmd);
	printf("cmd[0]: |%s|\n", cmd[0]);
	if (builtin(cmd, &sh->env_list) == 1)
	{
		free_2d(cmd);
		return ;
	}
	path = get_exe_path(cmd[0], &sh->env_list);
	child = ft_fork();
	if (child == 0)
	{
		if (execve(path, cmd, envp) == -1)
			exit(printf("Error: Command not found: %s.\n", *cmd));
	}
	waitpid(child, &status, 0);
	free(path);
	free_2d(cmd);
}

void	print_exec_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		printf("argv[%d]: |%s|\n", i, cmd[i]);
		i++;
	}
}
