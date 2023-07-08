/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:26:43 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/08 16:22:58 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	export(t_tree *head, t_list **env_list)
{
	char	**split;
	t_list	*tmp;
	t_env	*data;
	id_t	i;

	i = 1;
	tmp = *env_list;
	split = ft_split(head->value, ' ');
	if (split[1] == NULL)
	{
		data = (t_env *)tmp->content;
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n", data->key, data->value);
			tmp = tmp->next;
		}
	}
	else
	{
		while (split[i])
		{
			if (ft_isalpha(split[i][0]) == 0 && split[i][0] != '_')
				printf("export: '%s': not a valid identifier\n", split[i]);
			if (ft_strchr(split[i], '=') != NULL)
				add_link_list(split[i], env_list);
			i++;
		}
	}
}

void	modified_value(t_env *data_node, char *input)
{
	char	*value;
	char	*tmp;

	value = find_value(input);
	tmp = data_node->value;
	data_node->value = value;
	free(tmp);
}

void	add_link_list(char	*input, t_list	**env_list)
{
	char	*key;
	t_env	*data;
	t_list	*tmp;
	int		i;

	key = key_check(input);
	tmp = *env_list;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		i = ft_strncmp(data->key, key, ft_strlen(key));
		if (i == 0)
		{
			modified_value(data, input);
			break ;
		}
		tmp = tmp->next;
	}
	if (i != 0)
		creat_new_env_node(key, input, env_list);
}

char	*key_check(char *input)
{
	char	*key;

	if (input[0] == '$')
		input++;
	key = ft_substr(input, 0, ft_strchr(input, '=') - input);
	if (ft_strchr(key, '-') != NULL)
	{
		printf("export: '%s': not a valid identifier\n", key);
		return (NULL);
	}
	return (key);
}

char	*find_value(char *input)
{
	return (ft_substr(input, ft_strchr(input, '=') \
					- input + 1, ft_strlen(input) - \
					(ft_strchr(input, '=') - input)));
}
