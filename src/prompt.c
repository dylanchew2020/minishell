/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/08 17:04:21 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	prompt(t_root *root, char **envp)
{
	char	*cmd;
	t_list	*cmd_lexer;
	t_list	*tmp_lexer;
	t_tree	*head;
	t_list	*env_list;
	pid_t	child;
	int		status;

	env_list = NULL;
	env_link_list(envp, &env_list);
	while (1)
	{
		cmd = readline("\033[1;32mminishell$\033[0m ");
		if (*cmd)
		{
			cmd = expand(cmd, &env_list);
			exit_prompt(cmd);
			history_add(&root->history, cmd);
			cmd_lexer = lexer(cmd, &env_list);
			head = parser(cmd_lexer, ft_lstsize(cmd_lexer), root);
			print_tree(head, 0);
			if (builtin(head, &env_list) == 1)
				continue ;
			child = ft_fork();
			if (child == 0)
			{
				recurse_bst(head, envp, root);
				exit(0);
			}
			waitpid(-1, &status, 0);
			free_tree(head);
			while (cmd_lexer)
			{
				tmp_lexer = cmd_lexer->next;
				free(cmd_lexer);
				cmd_lexer = tmp_lexer;
			}
		}
		free(cmd);
	}
	history_clear(&root->history);
	free_env_list(&env_list);
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
