/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/05/30 19:43:13 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_root *root, char **envp)
{
	char	*cmd;

	(void) envp;
	while (1)
	{
		cmd = readline("MINISHELL>> ");
		// write(1, "MINISHELL>>", 11);
		// cmd = get_next_line(0);
		add_history(cmd);
		history_add(&root->history, cmd);
		if (!ft_strncmp(cmd, "history", 8))
			history_print(root->history);
		else
			printf("%s\n", cmd);
		exit_prompt(cmd);
		free(cmd);
	}
	clear_history();
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
