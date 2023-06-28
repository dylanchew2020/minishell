/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:06 by lchew             #+#    #+#             */
/*   Updated: 2023/06/21 21:35:56 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	children(t_tree *node, char **envp)
// {
// 	t_pipe	*data;
// 	pid_t	children[2];
// 	int		status;

// 	data = malloc(sizeof(t_pipe));
// 	ft_pipe(data->p);
// 	printf("parent %d \n", getpid());
// 	printf("1 pipe[0]: %d\n", data->p[0]);
// 	printf("1 pipe[1]: %d\n", data->p[1]);
// 	children[0] = ft_fork();
// 	if (children[0] == 0)
// 	{
// 		printf("first child %d\n", getpid());
// 		printf("first data->pipe[0] %d && data->pipe[1] %d\n", data->p[0], data->p[1]);
// 		dup2(data->p[1], 1);
// 		ft_close(data->p[1]);
// 		printf("close first child %d\n", getpid());
// 		ft_close(data->p[0]);
// 		printf("close first child %d\n", getpid());
// 		recurse_bst(node->left, envp);
// 	}
// 	// ft_close(data->p[1]);
// 	// printf("outside first child %d\n", getpid());
// 	// data->previous_fd = data->p[0];
// 	// ft_pipe(data->p);
// 	// printf("previous_fd %d\n", data->previous_fd);
// 	// printf("2 pipe[0]: %d\n", data->p[0]);
// 	// printf("2 pipe[1]: %d\n", data->p[1]);
// 	children[1] = ft_fork();
// 	if (children[1] == 0)
// 	{
// 		printf("second child %d\n", getpid());
// 		dup2(data->p[0], 0);
// 		ft_close(data->p[0]);
// 		printf("second child before recurse\n");
// 		recurse_bst(node->right, envp); 
// 	}
// 	// ft_close(data->p[0]);
// 	// ft_close(data->p[1]);
// 	waitpid(-1, &status, 0);
// 	free(data);
// }

int	pipe_num(t_link *head)
{
	int		i;
	t_link	*tmp;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if (*tmp->content == '|')
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	loop_middle_children(t_data	*data, char **envp, int num_pipe, pid_t *children)
{
	int i;
	int	status;

	i = 1;
	while (i < num_pipe)
	{
		data->prev_fd = data->p[0];
		ft_pipe(data->p);
		children[i] = ft_fork();
		if (children[i] == 0)
		{
			printf("middle child %d\n", getpid());
			ft_dup2(data->p[0], 0);
			ft_dup2(data->p[1], 1);
			ft_close(data->p[0]);
			ft_close(data->p[1]);
			if (data[i].rdin_fd != 0)
				ft_dup2(data[i].rdin_fd, 0);
			if (data[i].rdout_fd != 0)
				ft_dup2(data[i].rdout_fd, 1);
			execution(data[i].cmd, envp);
		}
		ft_close(data->p[1]);
		ft_close(data->prev_fd);
		waitpid(-1, &status, 0);
		i++;
	}
}

void	pipe_exec(t_data	*data, char **envp, int num_pipe)
{
	int status;
	pid_t children[num_pipe + 2];

	children[num_pipe + 1] = '\0';
	ft_pipe(data->p);
	printf("pipe[0]: %d\n", data->p[0]);
	printf("pipe[1]: %d\n", data->p[1]);
	children[0] = ft_fork();
	if (children[0] == 0)
	{
		printf("first child %d\n", getpid());
		ft_dup2(data->p[1], 1);
		ft_close(data->p[1]);
		ft_close(data->p[0]);
		if (data[0].rdin_fd != 0)
			ft_dup2(data[0].rdin_fd, 0);
		if (data[0].rdout_fd != 0)
			ft_dup2(data[0].rdout_fd, 1);
		execution(data[0].cmd, envp);
	}
	ft_close(data->p[1]);
	loop_middle_children(data, envp, num_pipe, children);
	children[num_pipe] = ft_fork();
	if (children[num_pipe] == 0)
	{
		printf("last child %d\n", getpid());
		ft_dup2(data->p[0], 0);
		ft_close(data->p[0]);
		if (data[num_pipe].rdin_fd != 0)
			ft_dup2(data[num_pipe].rdin_fd, 0);
		if (data[num_pipe].rdout_fd != 0)
			ft_dup2(data[num_pipe].rdout_fd, 1);
		execution(data[num_pipe].cmd, envp);
	}
	ft_close(data->p[0]);
	waitpid(-1, &status, 0);
}