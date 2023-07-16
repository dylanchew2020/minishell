/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:45:01 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/15 15:37:23 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_list **env_list, char *key)
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
