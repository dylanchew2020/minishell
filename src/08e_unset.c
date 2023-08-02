/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08e_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:45:01 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/02 17:08:07 by lchew            ###   ########.fr       */
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

/**
 * @brief Helper function to remove a specific environment variable.
 *
 * This function iterates through the linked list and searches for the
 * environment variable with the given key. Once found, it removes the node
 * from the linked list and deallocates the memory used by that node.
 *
 * @param key Pointer to the key of the environment variable to be removed.
 * @param env_list Double pointer to the linked list of environment variables.
 */
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
		if (ft_strncmp(data->key, *key, ft_strlen(data->key) + 1) == 0)
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
