/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/07/08 16:57:04 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	builtin(t_tree *head, t_list **env_list)
{
	char *value;

	// if (ft_strnstr(head->value, "unset", ft_strlen(head->value)) != NULL)
	// 	unset(head);
	if (ft_strnstr(head->value, "cd", ft_strlen("cd")) != NULL)
		cd(head->value);
	else if (ft_strnstr(head->value, "pwd", ft_strlen("pwd")) != NULL)
		pwd();
	else if (ft_strnstr(head->value, "export", ft_strlen("export")) != NULL)
		export(head, env_list);
	else if (ft_strnstr(head->value, "env", ft_strlen("env")) != NULL)
		get_env(env_list);
	else
		return (0);
	return (1);
}
