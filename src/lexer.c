/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:34:45 by lchew             #+#    #+#             */
/*   Updated: 2023/06/03 23:39:35 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_node_new(t_token token, char *value)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->token = token;
	ast->value = ft_strdup(value);
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

int	lexer(char *cmd)
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
	return (0);
}