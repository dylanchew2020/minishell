/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:00 by lchew             #+#    #+#             */
/*   Updated: 2023/07/20 20:00:29 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(t_root	*sh)
{
	(void) sh;
	// ft_tcgetattr(STDIN_FILENO, &sh->previous);
	// sh->current = sh->previous;
	// // sh->current.c_lflag &= ~ECHOCTL;
	// ft_tcsetattr(STDIN_FILENO, TCSANOW, &sh->current);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	return ;
}

//SIGINT - ctrl + c
//SIGQUIT - ctrl + \ //

// Function: int rl_redisplay ()

// Change what's displayed on the screen to reflect the current 
// contents of rl_line_buffer.
void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();		
		rl_redisplay();
		return ;
	}
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
