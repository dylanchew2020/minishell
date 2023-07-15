/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/07/15 19:18:29 by lchew            ###   ########.fr       */
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
