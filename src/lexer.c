/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:34:45 by lchew             #+#    #+#             */
/*   Updated: 2023/06/04 21:55:11 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lexer(char *cmd)
{
	char	**tokens;
	t_list	*lexer;
	t_list	*head;

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
	return (head);
}