/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utlis2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:42:24 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/29 12:09:09 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tcgetattr(int fd, struct termios *termios_p)
{
	if (tcgetattr(fd, termios_p) == -1)
	{
		perror("tcgetattr failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_tcsetattr(int fd, int optional_actions, struct termios *termios_p)
{
	if (tcsetattr(fd, optional_actions, termios_p) == -1)
	{
		perror("tcsetattr failed");
		exit(EXIT_FAILURE);
	}
}

void	free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	mini_error(char *str, int exit_code)
{
	ft_putstr_fd(str, 2);
	exit(exit_code);
}
