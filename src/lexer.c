/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:34:45 by lchew             #+#    #+#             */
/*   Updated: 2023/06/06 15:59:32 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lexer(char *cmd, char **envp)
{
	char	**tokens;
	t_list	*lexer;
	t_list	*head;

	(void) envp;
	tokens = ft_split(cmd, ' ');
	lexer = ft_lstnew((void *)ft_strdup(*tokens++));
	head = lexer;
	printf("%s\n", lexer->content);
	while (*tokens != NULL)
	{
		lexer->next = ft_lstnew((void *)ft_strdup(*tokens));
		lexer = lexer->next;
		printf("%s\n", lexer->content);
		++tokens;
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
	return (head);
}