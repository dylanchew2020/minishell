/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:34:45 by lchew             #+#    #+#             */
/*   Updated: 2023/06/05 17:26:26 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lexer(char *cmd, char **envp)
{
	char	**tokens;
	t_list	*lexer;
	t_list	*head;
	// char	**tmp;
	// char	**argv;

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
	// tmp = ft_calloc(2, sizeof(char *));
	// tmp[0] = ft_strjoin("PATH=", find_path(envp)[2]);
	// argv = ft_calloc(3, sizeof(char *));
	// argv[0] = head->content; //ft_strjoin("/bin/", head->content);
	// argv[1] = head->next->content;
	// printf("%s\n", argv[0]);
	// execve("/bin/ls", argv, tmp);
	return (head);
}