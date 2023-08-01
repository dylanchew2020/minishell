/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08h_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 10:30:27 by lchew             #+#    #+#             */
/*   Updated: 2023/08/01 14:49:20 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

int	exit_command(char **cmd, t_root *sh)
{
	int	i;

	i = 0;
	sh->exit_cmd_flag = 1;
	if (array2d_len(cmd) == 1)
		return (g_exit_status);
	while (ft_isdigit(cmd[1][i]) || cmd[1][i] == '-' || cmd[1][i] == '+')
		++i;
	if (ft_isdigit(cmd[1][i]) == 0 && cmd[1][i] != '\0')
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (EXIT_RANGE);
	}
	else
	{
		if (array2d_len(cmd) > 2)
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			sh->exit_cmd_flag = 0;
			return (EXIT_FAILURE);
		}
	}
	return (ft_atoi(cmd[1]));
}

void	exit_prompt(t_root *sh)
{
	if (sh->exit_cmd_flag == 1)
	{
		ft_close(sh->stdin_tmp);
		ft_close(sh->stdout_tmp);
		history_clear(&sh->history);
		ft_lstclear(&sh->env_list, del_data);
	}
}
