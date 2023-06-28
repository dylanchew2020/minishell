/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/06/28 18:02:56 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_root *root, char **envp)
{
	char	*cmd;
	char	**path;
	t_list	*cmd_lexer;
	t_tree	*head;
	pid_t	child;
	int		status;

	path = find_path();
	while (1)
	{
		cmd = readline("\033[1;32mminishell$\033[0m ");
		// printf("%d\n", (int)cmd[0]);
		exit_prompt(cmd);
		history_add(&root->history, cmd);
		cmd_lexer = lexer(cmd);
		head = parser(cmd_lexer, ft_lstsize(cmd_lexer), root);
		// print_tree(head, 0);
		// if (!ft_strncmp(cmd, "history", 8))
		// 	history_print(root->history);
		// else
		// 	printf("output: %s\n", cmd);
		// exec_cmd(head, envp);
		// printf("before %d\n", getpid());
		child = ft_fork();
		if (child == 0)
		{
			recurse_bst(head, envp);
			exit(0);
		}
		waitpid(-1, &status, 0);
		// printf("after %d\n", getpid());
		free(cmd);
	}
	history_clear(&root->history);
	return ;
}

void	exit_prompt(char *cmd)
{
	if (!cmd || !ft_strncmp(cmd, EXIT, 5))
	{
		free(cmd);
		clear_history();
		exit(0);
	}
}

void	print_tree(t_tree *root, int b)
{
	static int level;

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