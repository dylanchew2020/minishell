/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:00 by lchew             #+#    #+#             */
/*   Updated: 2023/07/30 17:22:23 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signum);
static void	signal_handler2(int signum);
static void	heredoc_signal(int signum);

/**
 * signals - Set up signal handlers based on the given mode.
 * @param sh: A pointer to a structure representing the shell (unused in this
 				implementation).
 * @param mode: An integer representing the mode for setting up signal handlers.
 *              Mode 1: Set signal_handler for SIGINT and SIGQUIT signals.
 *              Mode 0: Set signal_handler2 for SIGINT and SIGQUIT signals.
 *              Mode 2: Set heredoc_signal for SIGINT and ignore SIGQUIT signal.
 * @return: void
 */
void	signals(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
	}
	else if (mode == 0)
	{
		signal(SIGINT, signal_handler2);
		signal(SIGQUIT, signal_handler2);
	}
	else if (mode == 2)
	{
		signal(SIGINT, heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	return ;
}

/**
 * signal_handler - Handle signals for SIGINT and SIGQUIT during 
 					normal shell operation.
 * @param signum: The signal number.
 * @return: void
 */
static void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/**
 * signal_handler2 - Handle signals for SIGINT and SIGQUIT in a specific 
 					 mode (mode 0).
 * @param signum: The signal number.
 * @return: void
 */
static void	signal_handler2(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		return ;
	}
	if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
	}
}

/**
 * heredoc_signal - Handle the SIGINT signal during "heredoc"
 					 mode (mode 2).
 * @param signum: The signal number.
 * @return: void
 */
static void	heredoc_signal(int signum)
{
	if (signum == SIGINT)
		exit(EXIT_FAILURE);
}
