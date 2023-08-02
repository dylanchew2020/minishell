/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:16:13 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/02 17:56:50 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_expand_variable *data, char *cmd);
static char	*join_remaining(t_expand_variable *data, char *cmd);

/**
 * @brief Expands the command string, replacing variables with their values.
 *
 * This function processes the command string to replace variable references
 * with their corresponding values. It considers both single and double quotes,
 * handling them appropriately.
 *
 * @param cmd Original command string.
 * @param env_list List of environment variables.
 * @return Expanded command string with variable values replaced.
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

/**
 * @brief Initializes the data structure for command expansion.
 *
 * This function initializes the expansion-related variables, setting the
 * start pointer to the command and the dollar pointer to the first dollar
 * character found.
 *
 * @param data Structure containing expansion-related variables.
 * @param cmd Command string to be expanded.
 */
static void	init_data(t_expand_variable *data, char *cmd)
{
	data->n_cmd = NULL;
	data->substring = NULL;
	data->start = cmd;
	data->dollar_ptr = ft_strchr(cmd, DOLLAR);
}

/**
 * @brief Joins the remaining part of the command after expansion.
 *
 * This function creates a substring from the remaining part of the
 * command and joins it to the newly created command string, finalizing
 * the expansion process.
 *
 * @param data Structure containing expansion-related variables.
 * @param cmd Command string to be expanded.
 * @return Final expanded command string.
 */
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
