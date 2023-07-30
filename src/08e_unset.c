/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08e_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:45:01 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/30 16:57:19 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_helper(char **key, t_list **env_list);

/**
 * unset - Removes an environment variable from the linked list.
 *
 * @param env_list  Double pointer to the linked list of environment variables.
 * @param key       The key of the environment variable to be removed.
 */
int	unset(char **key, t_list **env_list)
{
	if (*key == NULL)
		return (EXIT_SUCCESS);
	while (*key)
	{
		unset_helper(key, env_list);
		++key;
	}
	return (EXIT_SUCCESS);
}

static void	unset_helper(char **key, t_list **env_list)
{
	t_list	*tmp;
	t_list	*prev;
	t_env	*data;
	
	tmp = *env_list;
	prev = NULL;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		if (ft_strnstr(data->key, *key, ft_strlen(*key)) != NULL)
		{
			if (prev == NULL)
				*env_list = tmp->next;
			else
				prev->next = tmp->next;
			ft_lstdelone(tmp, del_data);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}