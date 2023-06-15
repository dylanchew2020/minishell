/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/15 15:27:03 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	children(t_tree *node, char **envp)
{
	int		p[2];
	pid_t	children[2];
	int		status;

	ft_pipe(p);
	printf("write |%i|, read |%i|\n", p[1], p[0]);
	children[0] = ft_fork();
	if (children[0] == 0)
	{
		ft_close(p[0]);
		ft_dup2(p[1], STDOUT_FILENO);
		ft_close(p[1]);
		recurse_bst(node->left, envp);
	}
	children[1] = ft_fork();
	if (children[1] == 0)
	{
		ft_close(p[1]);
		ft_dup2(p[0], STDIN_FILENO);
		ft_close(p[0]);
		recurse_bst(node->right, envp);
	}
	ft_close(p[0]);
	ft_close(p[1]);
	waitpid(-1, &status, 0);
}
