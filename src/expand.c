/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:16:13 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/13 18:40:50 by tzi-qi           ###   ########.fr       */
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
	start = cmd;
	dollar = ft_strchr(cmd, '$');
	while (dollar)
	{
		single_quote = ft_strchr(start, '\'');
		if ((single_quote != NULL) && (single_quote - dollar < 0))
		{
			count = quote_count(single_quote);
			len = single_quote - start + count;
			if (tmp1 == NULL)
			{
				tmp1 = ft_substr(start, 0, len);
			}
			else
			{
				free(tmp3);
				tmp3 = ft_substr(start, 0, len);
				tmp1 = sub_or_join(tmp1, start, len, tmp3);
				free(tmp3);
			}
			dollar = start;
			dollar += len;
		}
		else
		{
			if (tmp1 == NULL)
				tmp1 = ft_substr(start, 0, dollar - start);
			else
			{
				free(tmp3);
				tmp3 = ft_substr(start, 0, dollar - start);
				tmp1 = sub_or_join(tmp1, start, dollar - start, tmp3);
				free(tmp3);
			}
			dollar++;
			key = key_check(dollar);
			value = existed_env(key, env_list);
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
	tmp3 = ft_substr(start, 0, ft_strlen(start));
	cmd = sub_or_join(tmp1, start, ft_strlen(start), tmp3);
	free(tmp3);
	return (cmd);
}
