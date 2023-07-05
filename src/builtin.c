/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/07/05 17:46:41 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	builtin(t_tree *head, t_list **env_list)
{

	(void)head;
	// while (tmp != NULL)
	// {
	// 	printf("%s\n", tmp->content);
	// 	tmp = tmp->next;
	// }
	// if (ft_strnstr(head->value, "unset", ft_strlen(head->value)) != NULL)
	// 	unset(head);
	// if (ft_strnstr(head->value, "export", ft_strlen(head->value)) != NULL)
	// 	export(head);
	// if (ft_strnstr(head->value, "pwd", ft_strlen(head->value)) != NULL)
	// 	pwd(head);
	if (ft_strnstr(head->value, "export", ft_strlen(head->value)) != NULL)
		export(head, env_list);
	else if (ft_strnstr(head->value, "env", ft_strlen(head->value)) != NULL)
		get_env(*env_list);
	else
		return (0);
	return (1);
}
