/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:26:51 by lchew             #+#    #+#             */
/*   Updated: 2023/06/28 18:42:22 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_root	root;
	(void)argc;
	(void)argv;

	// printf("argc: %d\n", argc);
	// printf("argv: %s\n", *argv);
	// while (*envp)
	// {
	// 	printf("%s\n", *envp);
	// 	envp++;
	// }
	init_root(&root);
	prompt(&root, envp);
	return (0);
}

void	init_root(t_root *root)
{
	root->history = NULL;
	init_token_check(root->tkchk);
}

void	free_2D(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	init_token_check(t_token_check	*tkchk)
{
	tkchk[0].token = RDAPP;
	tkchk[0].op = RDAPP_OP;
	tkchk[1].token = HEREDOC;
	tkchk[1].op = HEREDOC_OP;
	tkchk[2].token = RDIN;
	tkchk[2].op = RDIN_OP;
	tkchk[3].token = RDOUT;
	tkchk[3].op = RDOUT_OP;
	tkchk[4].token = PIPE;
	tkchk[4].op = PIPE_OP;
	tkchk[5].token = COMMAND;
	tkchk[5].op = NULL;
	tkchk[6].token = END;
	tkchk[6].op = NULL;
}
