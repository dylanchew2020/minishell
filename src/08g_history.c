/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08g_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:25:57 by lchew             #+#    #+#             */
/*   Updated: 2023/08/02 18:21:14 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new history node.
 *
 * Allocates and initializes a new history node with the given index and
 * command. The 'next' and 'prev' pointers are set to NULL.
 *
 * @param index The index for the new history node.
 * @param cmd The command for the new history node.
 * @return Pointer to the new history node, or NULL if allocation fails.
 */
t_history	*history_node_new(int index, void *cmd)
{
	t_history	*history;

	history = ft_calloc(1, sizeof(t_history));
	if (!history)
		return (NULL);
	history->id = index;
	history->cmd = ft_strdup(cmd);
	history->next = NULL;
	history->prev = NULL;
	return (history);
}

/**
 * history_clear - Frees the memory used by a doubly-linked list of history 
					  nodes,
 *                 and sets the list head pointer to NULL. It also clears 
					  the 
 *                 history maintained by the readline library. This function 
 *                 should be called when the shell is exiting or when history
					  is no longer needed.
 * @param history: A pointer to the head of the doubly-linked list of 
				      history nodes.
 *
 * @returns 
 * Void. Does not return any value and does not modify any global variables.
 */
void	history_clear(t_history **history)
{
	t_history	*tmp;
	t_history	*current;

	if (!history)
		return ;
	current = *history;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->cmd);
		free(tmp);
	}
	*history = NULL;
	clear_history();
}

/**
 * history_add - Adds a new history node to a doubly-linked list of 
					history nodes. It first checks if the provided command 
					is not NULL. If the command is valid, it increments the 
					index, then creates a new history node using the updated
					index and the command. It then appends the new node 
                 to the end of the list, correctly adjusting 'next' and 
					'prev' pointers.
 *
 * @param history: A pointer to the head of the doubly-linked list of 
					history nodes.
 * @param cmd: The command for the new history node.
 *
 * @returns 
 * Void. Does not return any value and does not modify any global variables.
 */
void	history_add(t_history **history, char *cmd)
{
	t_history	*new;
	t_history	*tmp;
	static int	index;

	if (!cmd)
		return ;
	add_history(cmd);
	new = history_node_new(++index, cmd);
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

/**
 * @brief Prints the history of commands.
 *
 * Iterates through a doubly-linked list of history nodes, printing the
 * index and command of each node.
 *
 * @param history A pointer to the head of the doubly-linked list of history 
 * 					nodes.
 * @return EXIT_SUCCESS, indicating successful execution.
 */
int	history_print(t_history *history)
{
	t_history	*tmp;

	tmp = history;
	while (tmp)
	{
		printf("%4d  %s\n", tmp->id, tmp->cmd);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
