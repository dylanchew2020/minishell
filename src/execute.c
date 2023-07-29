/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:08 by lchew             #+#    #+#             */
/*   Updated: 2023/07/29 12:21:35 by lchew            ###   ########.fr       */
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
	int		fd;

	fd = 0;
	if (node == NULL)
		return ;
	if (node->token == PIPE)
		children(node, envp, sh);
	else if (node->token == RDIN)
	{
		printf("rdin %i\n", fd);
		fd = rdin_fd(node->value, sh);
		if (fd < 0)
			return ;
		ft_dup2(fd, STDIN_FILENO);
		ft_close(fd);
		redir_arg(node, envp, sh);
		// recurse_rdin(node, envp, sh);
	}
	else if (node->token == RDOUT)
	{
		printf("rdout %i\n", fd);
		fd = rdout_fd(node->value, sh);
		if (fd < 0)
			return ;
		ft_dup2(fd, STDOUT_FILENO);
		ft_close(fd);
		redir_arg(node, envp, sh);
		// recurse_rdout(node, envp, sh);
	}
	else if (node->token == RDAPP)
	{
		printf("rdapp %i\n", fd);
		fd = rdapp_fd(node->value, sh);
		if (fd < 0)
			return ;
		ft_dup2(fd, STDOUT_FILENO);
		ft_close(fd);
		redir_arg(node, envp, sh);
		// recurse_rdapp(node, envp, sh);
	}
	else if (node->token == HEREDOC)
	{
		printf("heredoc %i\n", fd);
		ft_dup2(sh->stdin_tmp, STDIN_FILENO);
		fd = heredoc_fd(node->value, sh);
		if (fd < 0)
			return ;
		if (node->right == NULL || node->right->token != HEREDOC)
			ft_dup2(fd, STDIN_FILENO);
		ft_close(fd);
		redir_arg(node, envp, sh);
		// recurse_heredoc(node, envp, sh);
	}
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
		if (node->left != NULL && node->left->token == COMMAND &&\
			node->right->token == COMMAND)
			sh->add_arg = node->right->value;
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

	if (ft_strncmp(argv, "history", 7) == 0)
		return (history_print(sh->history));
	cmd = cmd_quote_handler(argv, ' ');
	if (sh->add_arg != NULL)
		cmd = cmd_join(cmd, cmd_quote_handler(sh->add_arg, ' '));
	print_exec_cmd(cmd);
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
	else
	{
		waitpid(child, &g_exit_status, 0);
		g_exit_status = exit_status(g_exit_status);
		free(path);
		free_2d(cmd);
	}
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
