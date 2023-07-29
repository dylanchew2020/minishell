/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:26:51 by lchew             #+#    #+#             */
/*   Updated: 2023/07/22 20:46:19 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_banner(void);

int g_exit_status = EXIT_SUCCESS;

int	main(int argc, char **argv, char **envp)
{
	t_root	sh;

	(void) argv;
	(void) argc;
	init_root(&sh);
	print_banner();
	prompt(&sh, envp);
	return (EXIT_SUCCESS);
}

void	init_root(t_root *sh)
{
	sh->history = NULL;
	init_token_check(sh->tkchk);
	sh->add_arg = NULL;
	sh->stdin_tmp = dup(STDIN_FILENO);
	sh->stdout_tmp = dup(STDOUT_FILENO);
	sh->env_list = NULL;
	sh->pipe = ft_calloc(2, sizeof(int));
	ft_tcgetattr(STDIN_FILENO, &sh->previous);
	ft_tcgetattr(STDIN_FILENO, &sh->current);
	sh->current.c_lflag &= ~ECHOCTL;
	ft_tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh->current);
	ft_tcsetattr(STDIN_FILENO, TCSANOW, &sh->current);
	sh->heredoc_flag = 0;
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
