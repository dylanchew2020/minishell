/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:41:17 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/26 19:42:38 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * sub_or_join - Helper function for string substitution or joining.
 *               If expanded_cmd is NULL, it creates a substring from start
 *               with length len.
 *               Otherwise, it joins expanded_cmd and substring and frees tmp2.
 *
 * @param expanded_cmd    The initial string or NULL if not yet defined.
 * @param start   The start position for the substring.
 * @param len     The length of the substring.
 * @param substring    The string to join with expanded_cmd.
 * @return        The resulting string after substitution or joining.
 */
char	*sub_or_join(char *cmd, char *start, int len, char *substring)
{
	char	*tmp;

	if (cmd == NULL)
		return (ft_substr(start, 0, len));
	tmp = cmd;
	cmd = ft_strjoin(cmd, substring);
	free(tmp);
	return (cmd);
}

void	init_data(t_expand_variable *data, char *cmd)
{
	data->expanded_cmd = NULL;
	data->substring = NULL;
	data->start = cmd;
	data->dollar_ptr = ft_strchr(cmd, '$');
}

char	*join_remaining(t_expand_variable *data, char *cmd)
{
	if (data->substring != NULL)
		free(data->substring);
	data->substring = ft_substr(data->start, 0, ft_strlen(data->start));
	cmd = sub_or_join(data->expanded_cmd, data->start, \
						ft_strlen(data->start), data->substring);
	free(data->substring);
	free(data);
	return (cmd);
}
