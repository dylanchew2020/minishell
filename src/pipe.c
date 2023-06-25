/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/25 18:57:38 by lchew            ###   ########.fr       */
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
	// printf("parent %d \n", getpid());
	// printf("1 pipe[0]: %d\n", data->p[0]);
	// printf("1 pipe[1]: %d\n", data->p[1]);
	children[0] = ft_fork();
	if (children[0] == 0)
	{
		// printf("first child, Fork = %d, PID = %d\n", children[0], getpid());
		// printf("first data->pipe[0] %d && data->pipe[1] %d\n", data->p[0], data->p[1]);
		dup2(data->p[1], STDOUT_FILENO);
		ft_close(data->p[1]);
		// printf("close first child %d\n", getpid());
		ft_close(data->p[0]);
		// printf("close first child %d\n", getpid());
		if (node->left == NULL)
			perror("syntax error near unexpected token `|'");
		else
		{
			// printf("Enter left node\n");
			recurse_bst(node->left, envp);
		}
	}
	// ft_close(data->p[1]);
	// printf("outside first child %d\n", getpid());
	// data->previous_fd = data->p[0];
	// ft_pipe(data->p);
	// printf("previous_fd %d\n", data->previous_fd);
	// printf("2 pipe[0]: %d\n", data->p[0]);
	// printf("2 pipe[1]: %d\n", data->p[1]);
	else
	{
		// printf("Parent 1, Fork = %d, PID = %d\n", children[0], getpid());
		children[1] = ft_fork();
		if (children[1] == 0)
		{
			// printf("Second child, Fork = %d, PID = %d\n", children[0], getpid());
			dup2(data->p[0], STDIN_FILENO);
			ft_close(data->p[0]);
			// printf("second child before recurse\n");
			recurse_bst(node->right, envp);
		}
		else
		{
			// printf("Parent 2, Fork = %d, PID = %d\n", children[0], getpid());
			waitpid(-1, &status, 0);
		}
		// ft_close(data->p[0]);
		// ft_close(data->p[1]);
	}
	free(data);
}
