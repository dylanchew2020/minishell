/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/07/29 14:17:28 by tzi-qi           ###   ########.fr       */
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
int	builtin(char **cmd, t_list **env_list)
{
	upper_to_lower(&cmd[0]);
	if (ft_strncmp(cmd[0], "unset", ft_strlen("unset") + 1) == 0)
		unset(cmd[1], env_list);
	else if (ft_strncmp(cmd[0], "cd", ft_strlen("cd") + 1) == 0)
		g_exit_status = cd(cmd, env_list);
	else if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd") + 1) == 0)
		g_exit_status = pwd();
	else if (ft_strncmp(cmd[0], "export", ft_strlen("export") + 1) == 0)
		g_exit_status = export(cmd, env_list);
	else if (ft_strncmp(cmd[0], "env", ft_strlen("env") + 1) == 0)
		get_env(env_list);
	else if (ft_strncmp(cmd[0], "echo", ft_strlen("echo") + 1) == 0)
		echo_builtin(cmd);
	else
		return (0);
	return (1);
}

void	upper_to_lower(char **str)
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