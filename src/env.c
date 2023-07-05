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
	t_env	*content;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		content = ft_calloc(1, sizeof(t_env));
		if (!content)
		{
			free(content);
			ft_lstclear((t_list **)env_list, free);
			return ;
		}
		content->key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		content->value = ft_substr(envp[i], ft_strchr(envp[i], '=') - envp[i] + 1, ft_strlen(envp[i]) - (ft_strchr(envp[i], '=') - envp[i]));
		node = ft_lstnew(content);
		ft_lstadd_back(env_list, node);
		i++;
	}
}

void	get_env(t_list *env_list)
{
	t_env	*data;

	while (env_list)
	{
		data = (t_env *)env_list->content;
		printf("%s=%s\n", data->key, data->value);
		env_list = env_list->next;
	}
}
