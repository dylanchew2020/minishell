/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:08 by lchew             #+#    #+#             */
/*   Updated: 2023/06/06 15:44:00 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_tree *node, char **envp)
{
	char	**path;
	int		i;
	char	**argv;

	i = -1;
	path = find_path(envp);
	argv = ft_calloc(4, sizeof(char *));
	if (node->token == COMMAND)
	{
		while (path[++i])
		{
			execve(ft_strjoin(path[i], node->value), argv, NULL);
			path++;
		}
	}
}