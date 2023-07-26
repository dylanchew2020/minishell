/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/07/26 15:32:48 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * builtin - Executes built-in commands based on the command array.
 *           Supported built-in commands: unset, cd, pwd, export, env.
 *
 * @param cmd       Double pointer to the command array.
 * @param env_list  Double pointer to the linked list containing environment variables.
 * @return          1 if a built-in command is executed, 0 otherwise.
 */
int	builtin(char **cmd, t_list **env_list)
{
	if (ft_strnstr(cmd[0], "unset", ft_strlen("unset")) != NULL)
		unset(cmd[1], env_list);
	else if (ft_strnstr(cmd[0], "cd", ft_strlen("cd")) != NULL)
		cd(cmd, env_list);
	else if (ft_strnstr(cmd[0], "pwd", ft_strlen("pwd")) != NULL)
		pwd();
	else if (ft_strnstr(cmd[0], "export", ft_strlen("export")) != NULL)
		export(cmd, env_list);
	else if ((ft_strnstr(cmd[0], "env", ft_strlen("env")) != NULL) \
			|| (ft_strnstr(cmd[0], "env", ft_strlen("env")) != NULL))
		get_env(env_list);
	else if ((ft_strnstr(cmd[0], "echo", ft_strlen("echo")) != NULL) \
			|| (ft_strnstr(cmd[0], "echo", ft_strlen("echo")) != NULL))
		echo_builtin(cmd);
	else
		return (0);
	return (1);
}
