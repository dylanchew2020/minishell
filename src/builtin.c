/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/07/15 16:34:41 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char **cmd, t_list **env_list)
{
	char *value;

	// if (ft_strnstr(head->value, "unset", ft_strlen(head->value)) != NULL)
	// 	unset(head);
	if (ft_strnstr(cmd[0], "cd", ft_strlen("cd")) != NULL)
		cd(cmd);
	else if (ft_strnstr(cmd[0], "pwd", ft_strlen("pwd")) != NULL)
		pwd();
	else if (ft_strnstr(cmd[0], "export", ft_strlen("export")) != NULL)
		export(cmd, env_list);
	else if ((ft_strnstr(cmd[0], "env", ft_strlen("env")) != NULL) \
			|| (ft_strnstr(cmd[0], "env", ft_strlen("env")) != NULL))
		get_env(env_list);
	else
		return (0);
	return (1);
}
