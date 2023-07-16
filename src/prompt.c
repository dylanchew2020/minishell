/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/15 17:00:59 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_root *sh, char **envp)
{
	char	*cmd;
	t_list	*cmd_lexer;
	t_list	*tmp_lexer;
	t_tree	*head;
	pid_t	child;
	int		status;
	char	cwd[256];

	env_link_list(envp, &sh->env_list);
	while (1)
	{
		printf("\033[1;32m%s", getcwd(cwd, sizeof(cwd)));
		cmd = readline("$\033[0m ");
		if (!cmd)
			continue ;
		if (*cmd)
		{
			cmd = expand(cmd, &sh->env_list);
			exit_prompt(cmd, sh);
			history_add(&sh->history, cmd);
			cmd_lexer = lexer(cmd);
			if (cmd_lexer == NULL)
				continue ;
			head = parser(cmd_lexer, ft_lstsize(cmd_lexer), sh);
			print_tree(head, 0);
			// if (builtin(head->value, &sh->env_list) == 1)
			// 	continue ;
			recurse_bst(head, envp, sh);
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
		// loop_env(&sh->env_list);
	}
	history_clear(&sh->history);
	free_env_list(&sh->env_list);
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
	printf("token (%u): (%s)\n", root->token, root->value);
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
