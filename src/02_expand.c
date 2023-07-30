/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:16:13 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/30 15:19:37 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_expand_variable *data, char *cmd);

/**
 * expand - Expands environment variables in the command string.
 *
 * @param cmd        The command string to expand.
 * @param env_list   Double ptr to the linked list containing env variables.
 * @return           The expanded command string.
 */
char	*expand(char *cmd, t_list **env_list)
{
	t_expand_variable	*data;

	data = ft_calloc(1, sizeof(t_expand_variable));
	init_data(data, cmd);
	while (data->dollar_ptr)
	{
		data->single_quote_ptr = ft_strchr(data->start, '\'');
		if ((data->single_quote_ptr != NULL) && \
			(data->single_quote_ptr - data->dollar_ptr < 0))
			single_quote(data);
		else
			join_dollar_ptr(data, env_list);
		data->start = data->dollar_ptr;
		data->dollar_ptr = ft_strchr(data->start, '$');
		if (data->dollar_ptr == NULL)
			break ;
		if (data->substring != NULL)
			free(data->substring);
		data->substring = ft_substr(data->start, 0, \
									data->dollar_ptr - data->start);
	}
	return (join_remaining(data, cmd));
}

static void	init_data(t_expand_variable *data, char *cmd)
{
	data->expanded_cmd = NULL;
	data->substring = NULL;
	data->start = cmd;
	data->dollar_ptr = ft_strchr(cmd, '$');
}