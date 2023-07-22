/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utlis2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:42:24 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/20 19:46:26 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tcgetattr(int fd, struct termios *termios_p)
{
	if (tcgetattr(fd, termios_p) == -1)
	{
		perror("tcgetattr failed");
		exit(1);
	}
}

void	ft_tcsetattr(int fd, int optional_actions, struct termios *termios_p)
{
	if (tcsetattr(fd, optional_actions, termios_p) == -1)
	{
		perror("tcsetattr failed");
		exit(1);
	}
}
