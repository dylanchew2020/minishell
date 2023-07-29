/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:16:13 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/29 18:15:19 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_exit_status(t_expand_variable *data)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(g_exit_status);
	data->expanded_cmd = sub_or_join(data->expanded_cmd, \
										data->start, 0, exit_status_str);
	free(exit_status_str);
	data->dollar_ptr++;
}

void	single_quote(t_expand_variable *data)
{
	data->count = quote_count(data->single_quote_ptr);
	data->len = data->single_quote_ptr - data->start + data->count;
	if (data->substring != NULL)
	{
		free(data->substring);
		data->substring = ft_substr(data->start, 0, data->len);
	}
	data->expanded_cmd = sub_or_join(data->expanded_cmd, \
					data->start, data->len, data->substring);
	data->dollar_ptr = data->start;
	data->dollar_ptr += data->len;
}

void	join_dollar_ptr(t_expand_variable *data, t_list **env_list)
{
	data->len = data->dollar_ptr - data->start;
	if (data->substring != NULL)
	{
		free(data->substring);
		data->substring = ft_substr(data->start, 0, data->len);
	}
	data->expanded_cmd = sub_or_join(data->expanded_cmd, \
									data->start, data->len, data->substring);
	data->dollar_ptr++;
	if (data->dollar_ptr[0] == '?')
		replace_exit_status(data);
	else
	{
		data->key = key_check(data->dollar_ptr);
		data->value = existed_env(data->key, env_list);
		if (data->value != NULL)
			data->expanded_cmd = sub_or_join(data->expanded_cmd, \
											data->start, 0, data->value);
		if (data->key != NULL)
		{
			data->dollar_ptr += ft_strlen(data->key);
			free(data->key);
		}
	}
}

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
