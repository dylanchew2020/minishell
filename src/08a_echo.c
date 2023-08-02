/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08a_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:28:02 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/02 17:11:47 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	loop_n(char *str);

/**
 * echo_command - Implements the behavior of the echo command in the shell.
 *                It prints the arguments to the standard output.
 *                Recognizes the "-n" option to suppress the trailing newline.
 *
 * @param cmd: An array of pointers to the arguments passed to the echo command.
 *
 * @returns EXIT_SUCCESS upon successful execution.
 */
int	echo_command(char **cmd)
{
	t_echo_var	echo;

	echo.flag = 0;
	echo.flag2 = 0;
	echo.i = 0;
	while (cmd[++echo.i])
	{
		if ((ft_strncmp(cmd[echo.i], "-n", ft_strlen("-n") + 1) == 0) \
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

/**
 * loop_n - Helper function to check if a string consists solely of 'n' 
 * 			characters.
 *          Used to verify the format of the "-n" option in the echo command.
 *
 * @param str: Pointer to the string to be checked.
 *
 * @returns 1 if the string consists solely of 'n' characters, 0 otherwise.
 */
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
