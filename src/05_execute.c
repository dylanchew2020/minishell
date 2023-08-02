/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:08 by lchew             #+#    #+#             */
/*   Updated: 2023/08/02 17:47:00 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(char *argv, char **envp, t_root *sh);

/**
 * @brief Recursively traverses the binary syntax tree.
 *
 * This function traverses the binary syntax tree and calls appropriate
 * handlers based on the token type of each node, including pipe handling,
 * input/output redirection, and command execution.
 *
 * @param node Current node in the binary syntax tree.
 * @param envp Environment variables array.
 * @param sh Root structure containing shell information.
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
 * @brief Executes a command.
 *
 * This function takes a command string, processes it into a command array,
 * and executes it. If the command is a built-in, it handles it accordingly.
 * It also sets the global exit status after execution.
 *
 * @param argv Command string.
 * @param envp Environment variables array.
 * @param sh Root structure containing shell information.
 */
static void	exec_cmd(char *argv, char **envp, t_root *sh)
{
	char	*path;
	char	**cmd;
	pid_t	child;

	cmd = cmd_quote_handler(argv, SPACE);
	if (sh->tree_arg_value != NULL)
		cmd = cmd_join(cmd, sh);
	if (builtin(cmd, sh) == 1)
		return ;
	path = get_exe_path(cmd[0], &sh->env_list);
	child = ft_fork();
	if (child == 0)
	{
		if (execve(path, cmd, envp) == -1)
		{
			ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
			printf("Error: Command not found: %s.\n", *cmd);
			exit(EXIT_NO_CMD);
		}
	}
	waitpid(child, &g_exit_status, 0);
	g_exit_status = exit_status(g_exit_status);
	free(path);
	free_2d(cmd);
}
