/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:16:13 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/15 20:06:01 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_2d(char **split)
{
	char	*result;
	char	*tmp;
	int		i;

	i = -1;
	result = "";
	while (split[++i])
	{
		printf("split |%s|\n", split[i]);
		tmp = ft_strjoin(result, split[i]);
		// if (split[i + 1] != NULL)
		result = ft_strjoin(tmp, " ");
		free(tmp);
	}
	printf("result |%s|\n", result);
	return (result);
}

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
				printf("tmp3 |%s|\n", tmp3);
			}
			tmp1 = sub_or_join(tmp1, start, len, tmp3);
			printf("tmp1 |%s|\n", tmp1);
			dollar = start;
			dollar += len;
		}
		else
		{
			len = dollar - start;
			printf("len |%d|\n", len);
			if (tmp3 != NULL)
			{
				printf("no tmp3 |%s|\n", tmp3);
				free(tmp3);
				tmp3 = ft_substr(start, 0, len);
				printf("no tmp3 |%s|\n", tmp3);
			}
			tmp1 = sub_or_join(tmp1, start, len, tmp3);
			printf("no tmp1 |%s|\n", tmp1);
			dollar++;
			printf("dollar |%s|\n", dollar);
			key = key_check(dollar);
			printf("key |%s|\n", key);
			value = existed_env(key, env_list);
			printf("value |%s|\n", value);
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
		printf("out if else tmp3 |%s|\n", tmp3);
	}
	if (tmp3 != NULL)
		free(tmp3);
	tmp3 = ft_substr(start, 0, ft_strlen(start));
	cmd = sub_or_join(tmp1, start, ft_strlen(start), tmp3);
	free(tmp3);
	printf("cmd |%s|\n", cmd);
	return (cmd);
}
