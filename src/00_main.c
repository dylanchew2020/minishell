/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:26:51 by lchew             #+#    #+#             */
/*   Updated: 2023/07/30 17:18:39 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_root(t_root *sh, char **envp);
static void	init_token_check(t_token_check	*tkchk);
static void	print_banner(void);

int	g_exit_status = EXIT_SUCCESS;

int	main(int argc, char **argv, char **envp)
{
	t_root	sh;

	(void) argv;
	(void) argc;
	if (init_root(&sh, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_banner();
	prompt(&sh, envp);
	exit_prompt(&sh);
	return (g_exit_status);
}

static int	init_root(t_root *sh, char **envp)
{
	sh->history = NULL;
	init_token_check(sh->tkchk);
	sh->tree_arg_value = NULL;
	sh->stdin_tmp = dup(STDIN_FILENO);
	sh->stdout_tmp = dup(STDOUT_FILENO);
	if (sh->stdin_tmp == -1 || sh->stdout_tmp == -1)
		return (EXIT_FAILURE);
	sh->env_list = NULL;
	if (env_link_list(envp, &sh->env_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	sh->pipe = ft_calloc(2, sizeof(int));
	if (!sh->pipe)
		return (EXIT_FAILURE);
	if (ft_tcgetattr(STDIN_FILENO, &sh->previous) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_tcgetattr(STDIN_FILENO, &sh->current) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	sh->current.c_lflag &= ~ECHOCTL;
	if (ft_tcsetattr(STDIN_FILENO, TCSANOW, &sh->current) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	sh->heredoc_flag = 0;
	sh->exit_cmd_flag = 0;
	return (EXIT_SUCCESS);
}

static void	init_token_check(t_token_check	*tkchk)
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

static void	print_banner(void)
{
	printf("\n");
	printf("\033[1;31m");
	printf("  __  __ _       _  _____ _          _ _ \n");
	printf(" |  \\/  (_)     (_)/ ____| |        | | |\n");
	printf(" | \\  / |_ _ __  _| (___ | |__   ___| | |\n");
	printf(" | |\\/| | | '_ \\| |\\___ \\| '_ \\ / _ \\ | |\n");
	printf(" | |  | | | | | | |____) | | | |  __/ | |\n");
	printf(" |_|  |_|_|_| |_|_|_____/|_| |_|\\___|_|_|\n");
	printf("\033[0m");
	printf("\n");
	printf("\033[1;32m");
	printf("          Welcome to MiniShell!\n");
	printf("\033[3m        Developed by Dylan & Ziqi\033[0m\n");
	printf("\033[0m");
	printf("\n");
}
