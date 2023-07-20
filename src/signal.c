/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:00 by lchew             #+#    #+#             */
/*   Updated: 2023/07/20 14:56:52 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//SIGINT - ctrl + c
//SIGQUIT - ctrl + \ //

// Function: int rl_redisplay ()

// Change what's displayed on the screen to reflect the current 
// contents of rl_line_buffer.
void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
