/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_minishell_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:42:24 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/30 17:18:58 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tcgetattr(int fd, struct termios *termios_p)
{
	if (tcgetattr(fd, termios_p) == -1)
	{
		perror("tcgetattr failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_tcsetattr(int fd, int optional_actions, struct termios *termios_p)
{
	if (tcsetattr(fd, optional_actions, termios_p) == -1)
	{
		perror("tcsetattr failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	array2d_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	str_to_lower(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] >= 'A' && (*str)[i] <= 'Z')
			(*str)[i] += 32;
		i++;
	}
}

void	print_exec_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		printf("argv[%d]: |%s|\n", i, cmd[i]);
		i++;
	}
}
