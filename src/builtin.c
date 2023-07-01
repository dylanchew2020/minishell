/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:11 by lchew             #+#    #+#             */
/*   Updated: 2023/07/01 18:11:52 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void    builtin(t_tree *head, char **envp)
{
	t_list	*env;
	t_list	*tmp;

	(void)head;
	env = NULL;
	env_link_list(envp, &env);
	printf("\nsize %i\n\n", ft_lstsize(env));
	tmp = env;
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
	// if (ft_strnstr(head->value, "export", ft_strlen(head->value)) != NULL)
	// 	export(head);
	if (ft_strnstr(head->value, "env", ft_strlen(head->value)) != NULL)
		get_env(env);
}
