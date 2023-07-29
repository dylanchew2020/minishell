/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:28:02 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/26 19:54:31 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	loop_n(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_builtin(char **cmd)
{
	int	i;
	int	flag;
	int	flag2;

	flag = 0;
	flag2 = 0;
	i = 0;
	while (cmd[++i])
	{
		if ((ft_strncmp(cmd[i], "-n", 2) == 0) && (loop_n((cmd[i] + 2)) == 1)\
			&& (flag2 == 0))
		{
			flag = 1;
			continue ;
		}
		else
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			write(1, " ", 1);
			flag2 = 1;
		}
	}
	if (flag != 1)
		write(1, "\n", 1);
}
