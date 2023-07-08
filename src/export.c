/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:26:43 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/08 13:55:22 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

//detext for "="
//else do nothing
//get the key from the head node->value
//get the value 
// put it into link list
//ft_lstadd back


void	export(t_tree *head, t_list **env_list)
{
	char	**split;
	t_list	*tmp;
	t_env	*data;
	id_t	i;

	printf("|%s|\n", head->value);
	i = 0;
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
		i++;
		while (split[i])
		{
			printf("%s\n", split[i]);
			 if (ft_isalpha(split[i][0]) == 0 && split[i][0] != '_')
				printf("export: '%s': not a valid identifier\n", split[i]);
			if (ft_strchr(split[i], '=') != NULL)
				add_link_list(split[i], env_list);
			i++;
		}
	}
}

void	add_link_list(char	*input, t_list	**env_list)
{
	char	*key;
	t_env	*data;
	t_env	*new_data;
	t_list	*node;
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
			printf("modified data here\n");
			break ;
		}
		tmp = tmp->next;
	}
	if (i != 0)
	{
		printf("creating new node\n");
		new_data = ft_calloc(1, sizeof(t_env));
		new_data->key = key;
		new_data->value = find_value(input);
		node = ft_lstnew(new_data);
		ft_lstadd_back(env_list, node);
	}
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
