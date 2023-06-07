/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/05/31 19:02:06 by tzi-qi           ###   ########.fr       */
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
		// printf("%s\n", path[i]);
	while (1)
	{
		cmd = readline("MINISHELL>> ");
		add_history(cmd);
		history_add(&root->history, cmd);
		if (!ft_strncmp(cmd, "history", 8))
			history_print(root->history);
		else
			printf("%s\n", cmd);
		printf("builtins %i\n", builtins_check(cmd));
		exit_prompt(cmd);
		free(cmd);
	}
	clear_history();
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
