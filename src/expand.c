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
 *               If tmp1 is NULL, it creates a substring from start with length len.
 *               Otherwise, it joins tmp1 and tmp3 and frees tmp2.
 *
 * @param tmp1    The initial string or NULL if not yet defined.
 * @param start   The start position for the substring.
 * @param len     The length of the substring.
 * @param tmp3    The string to join with tmp1.
 * @return        The resulting string after substitution or joining.
 */
char	*sub_or_join(char *tmp1, char *start, int len, char *tmp3)
{
	char	*tmp2;

	if (tmp1 == NULL)
		tmp1 = ft_substr(start, 0, len);
	else
	{
		tmp2 = tmp1;
		tmp1 = ft_strjoin(tmp1, tmp3);
		free(tmp2);
	}
	return (tmp1);
}

/**
 * expand - Expands environment variables in the command string.
 *
 * @param cmd        The command string to expand.
 * @param env_list   Double pointer to the linked list containing environment variables.
 * @return           The expanded command string.
 */
char	*expand(char *cmd, t_list **env_list)
{
	char	*tmp1;
	char	*tmp3;
	char	*dollar;
	char	*single_quote;
	char	*start;
	char	*key;
	char	*value;
	int		count;
	int		len;

	tmp1 = NULL;
	tmp3 = NULL;
	start = cmd;
	dollar = ft_strchr(cmd, '$');
	while (dollar)
	{
		single_quote = ft_strchr(start, '\'');
		if ((single_quote != NULL) && (single_quote - dollar < 0))
		{
			count = quote_count(single_quote);
			len = single_quote - start + count;
			if (tmp3 != NULL)
			{
				free(tmp3);
				tmp3 = ft_substr(start, 0, len);
			}
			tmp1 = sub_or_join(tmp1, start, len, tmp3);
			dollar = start;
			dollar += len;
		}
		else
		{
			len = dollar - start;
			// printf("len |%d|\n", len);
			if (tmp3 != NULL)
			{
				free(tmp3);
				tmp3 = ft_substr(start, 0, len);
			}
			tmp1 = sub_or_join(tmp1, start, len, tmp3);
			dollar++;
			// printf("dollar |%s|\n", dollar);
			key = key_check(dollar);
			// printf("key |%s|\n", key);
			value = existed_env(key, env_list);
			// printf("value |%s|\n", value);
			if (value != NULL)
				tmp1 = sub_or_join(tmp1, start, 0, value);
			if (key != NULL)
			{
				dollar += ft_strlen(key);
				free(key);
			}
		}
		start = dollar;
		dollar = ft_strchr(start, '$');
		if (dollar == NULL)
			break ;
		tmp3 = ft_substr(start, 0, dollar - start);
	}
	if (tmp3 != NULL)
		free(tmp3);
	tmp3 = ft_substr(start, 0, ft_strlen(start));
	cmd = sub_or_join(tmp1, start, ft_strlen(start), tmp3);
	free(tmp3);
	return (cmd);
}
