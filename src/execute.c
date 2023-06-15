/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:08 by lchew             #+#    #+#             */
/*   Updated: 2023/06/15 15:06:49 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_cmd(t_tree *node, char **envp)
// {
// 	char	**path;
// 	int		i;
// 	char	**argv;
// 	pid_t	pid;
// 	int		exec;
// 	char	*file;

// 	i = -1;
// 	if (node == NULL)
// 		return ;
// 	path = find_path();
// 	argv = ft_split(node->value, ' ');
// 	int j = 0;
// 	pid = fork();
// 	if (pid < 0)
// 		perror("Process creation failed");
// 	else if (pid == 0)
// 	{
// 		printf("I am the child, PID = %d\n", getpid());
// 		if (node->token == COMMAND)
// 		{
// 			// while (argv[j])
// 			// 	printf("argv : %s\n", argv[j++]);
// 			while (path[++i])
// 			{
// 				// printf("path : %s\n", path[i]);
// 				exec = execve(ft_strjoin(path[i], argv[0]), argv, NULL);
// 			}
// 			if (exec == -1)
// 			{
// 				printf("Error: %s: %s\n", strerror(errno), *argv);
// 				exit(0);
// 			}
// 		}
// 		printf("fd |%i|\n", rdin_fd(node->value));
// 	}
// 	else
// 	{
// 		printf("I am the parent, PID = %d\n", getpid());
// 		wait(NULL);
// 	}
// }


void	recurse_bst(t_tree *node, char **envp)
{
	if (node->value == NULL)
		return ;
	if (node->token == PIPE_OP)
	{
		// printf("pipe\n");
		children(node, envp);
	}
	else if (node->token == RDIN_OP)
	{
		printf("it enter here rdin\n");
		ft_dup2(rdin_fd(node->value), STDIN_FILENO);
		// printf("rdint safe\n");
	}
	else if (node->token == RDOUT_OP)
	{
		// printf("it enter e rdout\n");
		ft_dup2(rdout_fd(node->value), STDOUT_FILENO);
		// printf("rdout safe\n");
	}
	else if (node->token == COMMAND)
	{
		printf("executionnnnn \n");
		execution(node->value, envp);
	}
	recurse_bst(node->left, envp);
	recurse_bst(node->right, envp);
}

void	execution(char *argv, char **envp)
{
	char	*path;
	char	**cmd;

	path = the_legit_path(argv);
	cmd = ft_split(argv, ' ');
	if (execve(path, cmd, envp) == -1)
		exit(printf("Error: %s: %c\n", strerror(errno), *argv));
}



	// char	**tmp;
	// char	**argv;
	// tmp = ft_calloc(2, sizeof(char *));
	// tmp[0] = ft_strjoin("PATH=", find_path(envp)[2]);
	// argv = ft_calloc(5, sizeof(char *));
	// int i = 0;
	// t_list *node = head;
	// while (i < 5 && node != NULL)
	// {
	// 	argv[i++] = node->content;
	// 	node = node->next;
	// }
	// // argv[0] = head->content; //ft_strjoin("/bin/", head->content);
	// // argv[1] = head->next->content;
	// printf("argv : %s\n", argv[0]);
	// execve("/usr/bin/touch", argv, tmp);

