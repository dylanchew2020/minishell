/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:08 by lchew             #+#    #+#             */
/*   Updated: 2023/06/11 21:04:26 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_tree *node, char **envp)
{
	char	**path;
	int		i;
	char	**argv;
	pid_t	pid;
	int		exec;

	i = -1;
	if (node == NULL)
		return ;
	path = find_path();
	argv = ft_split(node->value, ' ');
	int j = 0;
	pid = fork();
	if (pid < 0)
		perror("Process creation failed");
	else if (pid == 0)
	{
		printf("I am the child, PID = %d\n", getpid());
		if (node->token == COMMAND)
		{
			// while (argv[j])
			// 	printf("argv : %s\n", argv[j++]);
			while (path[++i])
			{
				// printf("path : %s\n", path[i]);
				exec = execve(ft_strjoin(path[i], argv[0]), argv, NULL);
				// printf("exec : %d\n", exec);
			}
			if (exec == -1)
			{
				printf("Error: %s: %s\n", strerror(errno), *argv);
				exit(0);
			}
		}
	}
	else
	{
		printf("I am the parent, PID = %d\n", getpid());
		wait(NULL);
	}
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