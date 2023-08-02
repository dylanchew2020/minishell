/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:16:13 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/02 15:35:48 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_expand_variable *data, char *cmd);
static char	*join_remaining(t_expand_variable *data, char *cmd);

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
		data->single_quote_ptr = ft_strchr(data->start, SINGLE_QUOTE);
		if ((data->single_quote_ptr != NULL) && \
			(data->single_quote_ptr < data->dollar_ptr) && \
			(data->single_quote_ptr < ft_strchr(data->start, DOUBLE_QUOTE)))
			single_quote(data);
		else
			join_dollar_ptr(data, env_list);
		data->start = data->dollar_ptr;
		data->dollar_ptr = ft_strchr(data->start, DOLLAR);
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
	data->n_cmd = NULL;
	data->substring = NULL;
	data->start = cmd;
	data->dollar_ptr = ft_strchr(cmd, DOLLAR);
}

static char	*join_remaining(t_expand_variable *data, char *cmd)
{
	if (data->substring != NULL)
		free(data->substring);
	data->substring = ft_substr(data->start, 0, ft_strlen(data->start));
	cmd = sub_or_join(data->n_cmd, data->start, \
						ft_strlen(data->start), data->substring);
	free(data->substring);
	free(data);
	return (cmd);
}
