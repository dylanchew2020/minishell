/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:25:57 by lchew             #+#    #+#             */
/*   Updated: 2023/05/30 19:40:49 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*history_lstnew(int index, void *cmd)
{
	t_history	*history;

	history = ft_calloc(1, sizeof(t_history));
	if (!history)
		return (NULL);
	history->id = index;
	history->cmd = cmd;
	history->next = NULL;
	history->prev = NULL;
	return (history);
}

void	history_add(t_history **history, char *cmd)
{
	t_history	*new;
	t_history	*tmp;
	static int	index;

	new = history_lstnew(++index, cmd);
	if (!(*history))
	{
		*history = new;
	}
	else
	{
		tmp = *history;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	history_print(t_history *history)
{
	t_history	*tmp;

	tmp = history;
	while (tmp)
	{
		printf("%4d  %s\n", tmp->id, tmp->cmd);
		tmp = tmp->next;
	}
}
