/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:08 by lchew             #+#    #+#             */
/*   Updated: 2023/07/30 16:31:40 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(char *argv, char **envp, t_root *sh);

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
		pipe_handler(node, envp, sh);
	else if (node->token == RDIN)
		rdin_handler(node, envp, sh);
	else if (node->token == RDOUT)
		rdout_handler(node, envp, sh);
	else if (node->token == RDAPP)
		rdapp_handler(node, envp, sh);
	else if (node->token == HEREDOC)
		heredoc_handler(node, envp, sh);
	else if (node->token == COMMAND)
		exec_cmd(node->value, envp, sh);
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
static void	exec_cmd(char *argv, char **envp, t_root *sh)
{
	char	*path;
	char	**cmd;
	pid_t	child;

	cmd = cmd_quote_handler(argv, ' ');
	if (sh->tree_arg_value != NULL)
		cmd = cmd_join(cmd, sh);
	if (builtin(cmd, sh) == 1)
	{
		free_2d(cmd);
		return ;
	}
	path = get_exe_path(cmd[0], &sh->env_list);
	child = ft_fork();
	if (child == 0)
	{
		if (execve(path, cmd, envp) == -1)
		{
			printf("Error: Command not found: %s.\n", *cmd);
			exit(EXIT_NO_CMD);
		}
	}
	waitpid(child, &g_exit_status, 0);
	g_exit_status = exit_status(g_exit_status);
	free(path);
	free_2d(cmd);
}
