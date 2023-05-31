/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:26:51 by lchew             #+#    #+#             */
/*   Updated: 2023/05/31 19:04:59 by tzi-qi           ###   ########.fr       */
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
}
