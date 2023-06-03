/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/06/03 17:44:29 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_root *root, char **envp)
{
	char	*cmd;
	char	**path;
	int		i = -1;

	path = find_path(envp);
	while (path[++i])
		printf("%s\n", path[i]);
	while (1)
	{
		cmd = readline("\033[1;32mminishell$\033[0m ");
		history_add(&root->history, cmd);
		lexer(cmd);
		if (!ft_strncmp(cmd, "history", 8))
			history_print(root->history);
		else
			printf("%s\n", cmd);
		exit_prompt(cmd);
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
