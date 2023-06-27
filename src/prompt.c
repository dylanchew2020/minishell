/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/06/25 18:56:28 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_root *root, char **envp)
{
	char	*cmd;
	char	**path;
	t_list	*cmd_lexer;
	t_list	*iter;
	t_tree	*head;
	pid_t	child;
	int		status;

	path = find_path();
	while (1)
	{
		cmd = readline("\033[1;32mminishell$\033[0m ");
		if (exit_prompt(cmd) == 0)
		{
			history_add(&root->history, cmd);
			if (!ft_strncmp(cmd, "history", 8))
				history_print(root->history);
			else
			{
				cmd_lexer = lexer(cmd);
				// iter = cmd_lexer;
				// while (iter->next != NULL)
				// {
				// 	printf("%s\n", (char *)iter->content);
				// 	iter = iter->next;
				// }
				head = parser(cmd_lexer, ft_lstsize(cmd_lexer), root);
				// print_tree(head, 0);
				// exec_cmd(head, envp);
				// printf("before %d\n", getpid());
				if (head->token == PIPE)
					recurse_bst(head, envp);
				else
				{
					child = ft_fork();
					if (child == 0)
					{
						// printf("Prompt child, Fork = %d, PID = %d\n", child, getpid());
						recurse_bst(head, envp);
						// printf("Check if this is printed\n");
					}
					else
					{
						// printf("Prompt parent, Fork = %d, PID = %d\n", child, getpid());
						waitpid(-1, &status, 0);
						// printf("Check parent wait finished\n");
					}
					// printf("after %d\n", getpid());
					free(cmd);
				}
			}
		}
	}
	history_clear(&root->history);
	return ;
}

int	exit_prompt(char *cmd)
{
	if (!cmd || !ft_strncmp(cmd, EXIT, 5))
	{
		free(cmd);
		clear_history();
		exit(0);
	}
	return (0);
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
