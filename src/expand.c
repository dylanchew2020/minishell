/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:16:13 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/18 15:53:11 by lchew            ###   ########.fr       */
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

/**
 * expand - Expands environment variables in the command string.
 *
 * @param cmd        The command string to expand.
 * @param env_list   Double ptr to the linked list containing env variables.
 * @return           The expanded command string.
 */
char	*expand(char *cmd, t_list **env_list)
{
	char	*expanded_cmd;
	char	*substring;
	char	*dollar_ptr;
	char	*single_quote_ptr;
	char	*start;
	char	*key;
	char	*value;
	int		count;
	int		len;

	expanded_cmd = NULL;
	substring = NULL;
	start = cmd;
	dollar_ptr = ft_strchr(cmd, '$');
	while (dollar_ptr)
	{
		single_quote_ptr = ft_strchr(start, '\'');
		if ((single_quote_ptr != NULL) && (single_quote_ptr - dollar_ptr < 0))
		{
			count = quote_count(single_quote_ptr);
			len = single_quote_ptr - start + count;
			if (substring != NULL)
			{
				free(substring);
				substring = ft_substr(start, 0, len);
			}
			expanded_cmd = sub_or_join(expanded_cmd, start, len, substring);
			dollar_ptr = start;
			dollar_ptr += len;
		}
		else
		{
			len = dollar_ptr - start;
			if (substring != NULL)
			{
				free(substring);
				substring = ft_substr(start, 0, len);
			}
			expanded_cmd = sub_or_join(expanded_cmd, start, len, substring);
			dollar_ptr++;
			key = key_check(dollar_ptr + 1);
			value = existed_env(key, env_list);
			if (value != NULL)
				expanded_cmd = sub_or_join(expanded_cmd, start, 0, value);
			if (key != NULL)
			{
				dollar_ptr += ft_strlen(key);
				free(key);
			}
		}
		start = dollar_ptr;
		dollar_ptr = ft_strchr(start, '$');
		if (dollar_ptr == NULL)
			break ;
		if (substring != NULL)
			free(substring);
		substring = ft_substr(start, 0, dollar_ptr - start);
	}
	if (substring != NULL)
		free(substring);
	substring = ft_substr(start, 0, ft_strlen(start));
	cmd = sub_or_join(expanded_cmd, start, ft_strlen(start), substring);
	free(substring);
	return (cmd);
}
