/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/07/30 16:41:47 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * builtin - Executes built-in commands based on the command array.
 *           Supported built-in commands: unset, cd, pwd, export, env.
 *
 * @param cmd       Double pointer to the command array.
 * @param env_list  Double pointer to the linked list containing environment
					   variables.
 * @return          1 if a built-in command is executed, 0 otherwise.
 */
int	builtin(char **cmd, t_root *sh)
{
	str_to_lower(&cmd[0]);
	if (ft_strncmp(cmd[0], "echo", ft_strlen("echo") + 1) == 0)
		g_exit_status = echo_command(cmd);
	else if (ft_strncmp(cmd[0], "cd", ft_strlen("cd") + 1) == 0)
		g_exit_status = cd(cmd, &sh->env_list);
	else if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd") + 1) == 0)
		g_exit_status = pwd();
	else if (ft_strncmp(cmd[0], "export", ft_strlen("export") + 1) == 0)
		g_exit_status = export(cmd, &sh->env_list);
	else if (ft_strncmp(cmd[0], "unset", ft_strlen("unset") + 1) == 0)
		g_exit_status = unset(++cmd, &sh->env_list);
	else if (ft_strncmp(cmd[0], "env", ft_strlen("env") + 1) == 0)
		g_exit_status = get_env(&sh->env_list);
	else if (ft_strncmp(cmd[0], "history", ft_strlen("history") + 1) == 0)
		g_exit_status = history_print(sh->history);
	else if (ft_strncmp(cmd[0], "exit", ft_strlen("exit") + 1) == 0)
		g_exit_status = exit_command(cmd, sh);
	else
		return (0);
	return (1);
}
