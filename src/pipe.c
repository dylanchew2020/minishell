/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/19 17:33:25 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	children(t_tree *node, char **envp)
{
	t_pipe	*data;
	pid_t	children[2];
	int		status;

	data = malloc(sizeof(t_pipe));
	ft_pipe(data->p);
	printf("1 pipe[0]: %d\n", data->p[0]);
	printf("1 pipe[1]: %d\n", data->p[1]);
	children[0] = ft_fork();
	if (children[0] == 0)
	{
		printf("first child %d\n", getpid());
		ft_close(data->p[0]);
		ft_dup2(data->p[1], STDOUT_FILENO);
		ft_close(data->p[1]);
		recurse_bst(node->left, envp);
	}
	waitpid(children[0], &status, 0);
	ft_close(data->p[1]);
	data->previous_fd = data->p[0];
	ft_pipe(data->p);
	printf("2 pipe[0]: %d\n", data->p[0]);
	printf("2 pipe[1]: %d\n", data->p[1]);
	printf("parent %d \n", getpid());
	children[1] = ft_fork();
	if (children[1] == 0)
	{
		printf("second child %d\n", getpid());
		ft_close(data->p[0]);
		ft_dup2(data->previous_fd, STDIN_FILENO);
		ft_close(data->previous_fd);
		ft_dup2(data->p[1], STDOUT_FILENO);
		ft_close(data->p[1]);
		recurse_bst(node->right, envp);
	}
	ft_close(data->p[0]);
	ft_close(data->p[1]);
	waitpid(-1, &status, 0);
}
