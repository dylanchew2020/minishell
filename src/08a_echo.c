/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08a_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:28:02 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/30 16:20:14 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	loop_n(char *str);

int	echo_command(char **cmd)
{
	t_echo_var	echo;

	echo.flag = 0;
	echo.flag2 = 0;
	echo.i = 0;
	while (cmd[++echo.i])
	{
		if ((ft_strncmp(cmd[echo.i], "-n", 2) == 0) \
			&& (loop_n((cmd[echo.i] + 2)) == 1) \
			&& (echo.flag2 == 0))
		{
			echo.flag = 1;
			continue ;
		}
		else
		{
			write(1, cmd[echo.i], ft_strlen(cmd[echo.i]));
			if (cmd[echo.i + 1] != NULL)
				write(1, " ", 1);
			echo.flag2 = 1;
		}
	}
	if (echo.flag != 1)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

static int	loop_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}