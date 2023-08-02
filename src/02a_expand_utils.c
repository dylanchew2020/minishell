/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02a_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:41:17 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/02 15:36:21 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quote(t_expand_variable *data)
{
	data->count = quote_count(data->single_quote_ptr);
	data->len = data->single_quote_ptr - data->start + data->count;
	if (data->substring != NULL)
	{
		free(data->substring);
		data->substring = ft_substr(data->start, 0, data->len);
	}
	data->n_cmd = sub_or_join(data->n_cmd, \
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
	data->n_cmd = sub_or_join(data->n_cmd, \
									data->start, data->len, data->substring);
	data->dollar_ptr++;
	if (data->dollar_ptr[0] == '?')
		replace_exit_status(data);
	else
	{
		data->key = key_check(data->dollar_ptr);
		data->value = existed_env(data->key, env_list);
		if (data->value != NULL)
			data->n_cmd = sub_or_join(data->n_cmd, data->start, 0, data->value);
		if (data->key == NULL)
			data->n_cmd = sub_or_join(data->n_cmd, data->start, 0, "$");
		else if (data->key != NULL)
		{
			data->dollar_ptr += ft_strlen(data->key);
			free(data->key);
		}
	}
}

void	replace_exit_status(t_expand_variable *data)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(g_exit_status);
	data->n_cmd = sub_or_join(data->n_cmd, \
										data->start, 0, exit_status_str);
	free(exit_status_str);
	data->dollar_ptr++;
}

/**
 * sub_or_join - Helper function for string substitution or joining.
 *               If n_cmd is NULL, it creates a substring from start
 *               with length len.
 *               Otherwise, it joins n_cmd and substring and frees tmp2.
 *
 * @param n_cmd    The initial string or NULL if not yet defined.
 * @param start   The start position for the substring.
 * @param len     The length of the substring.
 * @param substring    The string to join with n_cmd.
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

char	*key_check(char *input)
{
	int		i;
	char	*key;

	i = 0;
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	if (i == 0)
		key = NULL;
	else
		key = ft_substr(input, 0, i);
	return (key);
}
