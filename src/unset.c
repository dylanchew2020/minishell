/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:45:01 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/22 15:45:03 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * unset - Removes an environment variable from the linked list.
 *
 * @param env_list  Double pointer to the linked list of environment variables.
 * @param key       The key of the environment variable to be removed.
 */
void	unset(char *key, t_list **env_list)
{
	t_list	*tmp;
	t_list	*prev;
	t_env	*data;


	if (key == NULL)
		return ;
	tmp = *env_list;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		if (ft_strnstr(data->key, key, ft_strlen(key)) != NULL)
		{
			prev->next = tmp->next;
			ft_lstdelone(tmp, del_data);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
