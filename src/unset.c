/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:45:01 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/26 17:31:51 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * unset - Removes an environment variable from the linked list.
 *
 * @param env_list  Double pointer to the linked list of environment variables.
 * @param key       The key of the environment variable to be removed.
 */
int	unset(char *key, t_list **env_list)
{
	t_list	*tmp;
	t_list	*prev;
	t_env	*data;

	if (key == NULL)
		return (EXIT_SUCCESS);
	tmp = *env_list;
	prev = NULL;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		if (ft_strnstr(data->key, key, ft_strlen(key)) != NULL)
		{
			if (prev == NULL)
				*env_list = tmp->next;
			else if (tmp->next == NULL)
				prev->next = tmp->next;
			ft_lstdelone(tmp, del_data);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
