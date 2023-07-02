/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:10 by lchew             #+#    #+#             */
/*   Updated: 2023/07/01 18:11:38 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

//error_code
//store env in linked list using key=value format

void	env_link_list(char **envp, t_list **env_list)
{
	int		i;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		node = ft_lstnew(envp[i]);
		if (!node)
		{
			ft_lstclear(env_list, free);
			return ;
		}
		ft_lstadd_back(env_list, node);
		i++;
	}
}

void	get_env(t_list *env_list)
{
	while (env_list)
	{
		printf("%s\n", (char *)env_list->content);
		env_list = env_list->next;
	}
}
