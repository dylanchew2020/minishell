/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:38:59 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/29 16:18:29 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * del_data - Frees the memory associated with a t_env struct.
 *
 * @param content  Pointer to the t_env struct to be freed.
 */
void	del_data(void	*content)
{
	t_env	*data;

	data = (t_env *)content;
	free(data->key);
	free(data->value);
	free(data);
}

void	reset_data(t_root *sh, t_list **cmd_lexer, t_tree **head)
{
	t_list	*current;
	t_list	*next;

	ft_dup2(sh->stdin_tmp, STDIN_FILENO);
	ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
	ft_tcsetattr(STDIN_FILENO, TCSANOW, &sh->current);
	if (access(".here_doc_tmp", F_OK & X_OK) == 0)
		unlink(".here_doc_tmp");
	free_tree(*head);
	sh->tree_arg_value = NULL;
	current = *cmd_lexer;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
