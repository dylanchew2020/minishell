/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/06/28 19:32:25 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_root *sh, char **envp)
{
	char	*cmd;
	char	**path;
	t_list	*cmd_lexer;
	t_list	*tmp_lexer;
	t_tree	*head;
	pid_t	child;
	int		status;
	

	
	path = find_path();
	while (1)
	{
		cmd = readline("\033[1;32mminishell$\033[0m ");
		if (!cmd)
			continue ;
		if (*cmd)
		{
			exit_prompt(cmd, sh);
			history_add(&sh->history, cmd);
			cmd_lexer = lexer(cmd);
			head = parser(cmd_lexer, ft_lstsize(cmd_lexer), sh);
			// print_tree(head, 0);
			// child = ft_fork();
			// if (child == 0)
			// {
				recurse_bst(head, envp, sh);
				// free(sh->path);
				// free_2d(sh->cmd);
				// exit(0);
			// }
			// waitpid(-1, &status, 0);
			free_tree(head);
			while (cmd_lexer)
			{
				tmp_lexer = cmd_lexer->next;
				free(cmd_lexer);
				cmd_lexer = tmp_lexer;
			}
		}
		free(cmd);
		ft_dup2(sh->stdin_tmp, STDIN_FILENO);
		ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
	}
	history_clear(&sh->history);
	return ;
}

void	exit_prompt(char *cmd, t_root *sh)
{
	if (!cmd || !ft_strncmp(cmd, EXIT, 5))
	{
		free(cmd);
		clear_history();
		ft_close(sh->stdin_tmp);
		ft_close(sh->stdout_tmp);
		int fd = open("1.tmp", O_RDONLY);
		dprintf(2, "fd = %d\n", fd);
		close(fd);
		exit(0);
	}
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
	printf("%u : %s\n", root->token, root->value);
	printf("left %i  ", level);
	print_tree(root->left, 0);
	printf("right %i  ", level);
	print_tree(root->right, 0);
	--level;
}

void	free_tree(t_tree *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	free(node->value);
	free(node);
}
