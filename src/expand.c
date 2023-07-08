/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:16:13 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/08 15:41:32 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
		tmp = ft_strjoin(result, split[i]);
		result = ft_strjoin(tmp, " ");
		free(tmp);
		printf("result   |%s|\n", result);
	}
	return (result);
}

char	*expand(char *cmd, t_list **env_list)
{
	char	*key;
	char	*value;
	char	*tmp;
	char	*cmd_value;
	char	**split;
	int		i;


	if (ft_strchr(cmd, '$') != NULL)
	{
		split = ft_split(cmd, ' ');
		i = 0;
		while (split[i])
		{
			if (split[i][0] == '$')
			{
				key = key_check(split[i]);
				value = existed_env(key, env_list);
				cmd_value = find_value(split[i]);
				if (value != NULL)
				{
					if (ft_strchr(split[i], '=') != NULL)
					{
						tmp = ft_strjoin(value, "=");
						value = tmp;
					}
					tmp = ft_strjoin(value, cmd_value);
				}
				else
					tmp = "";
				free(split[i]);
				split[i] = ft_strdup(tmp);
				free(tmp);
				free(key);
				free(cmd_value);
				break ;
			}
			i++;
		}
		free(cmd);
		cmd = join_2d(split);
		free_2d(split);
	}
	return (cmd);
}
