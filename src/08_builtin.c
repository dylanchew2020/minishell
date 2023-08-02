/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/08/02 17:37:18 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes a built-in shell command.
 *
 * This function checks the given command and executes the corresponding
 * built-in shell command such as echo, cd, pwd, export, unset, env,
 * history, or exit. It sets the global exit status accordingly.
 *
 * @param cmd Array of strings representing the command and its arguments.
 * @param sh Pointer to the shell root structure.
 * @return 1 if the command is a built-in and executed successfully,
 *         0 if the command is not a built-in.
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
		g_exit_status = unset(cmd + 1, &sh->env_list);
	else if (ft_strncmp(cmd[0], "env", ft_strlen("env") + 1) == 0)
		g_exit_status = get_env(&sh->env_list);
	else if (ft_strncmp(cmd[0], "history", ft_strlen("history") + 1) == 0)
		g_exit_status = history_print(sh->history);
	else if (ft_strncmp(cmd[0], "exit", ft_strlen("exit") + 1) == 0)
		g_exit_status = exit_command(cmd, sh);
	else
		return (0);
	free_2d(cmd);
	return (1);
}
