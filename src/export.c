/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:26:43 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/15 16:35:29 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * export - Handles the export command, which either displays the current environment variables
 *          or adds new environment variables.
 *
 * @param cmd       Double pointer to the command array.
 * @param env_list  Double pointer to the linked list containing environment variables.
 */
void	export(char **cmd, t_list **env_list)
{
	char	**split;
	t_list	*tmp;
	t_env	*data;
	id_t	i;

	i = 1;
	tmp = *env_list;
	// split = ft_split(cmd, ' ');
	split = cmd;
	if (split[1] == NULL)
	{
		while (tmp)
		{
			data = (t_env *)tmp->content;
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
	free_2d(split);
}

/**
 * modified_value - Modifies the value of an environment variable node.
 *
 * @param data_node  Pointer to the environment variable node.
 * @param input      The new input value.
 */
void	modified_value(t_env *data_node, char *input)
{
	char	*value;
	char	*tmp;

	value = find_value(input);
	tmp = data_node->value;
	data_node->value = value;
	free(tmp);
}

/**
 * modified_value - Modifies the value of an environment variable node.
 *
 * @param data_node  Pointer to the environment variable node.
 * @param input      The new input value.
 */
void	add_link_list(char	*input, t_list	**env_list)
{
	char	*key;
	t_env	*data;
	t_list	*tmp;
	int		i;

	printf("input |%s|\n", input);
	key = key_check(input);
	printf("key |%s|\n", key);
	if (key == NULL)
		return ;
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

/**
 * key_check - Checks if the input string is a valid identifier (environment variable key).
 *
 * @param input   The input string to check.
 * @return        The extracted key if it's a valid identifier, or NULL otherwise.
 */
char	*key_check(char *input)
{
	int		i;
	char	*key;

	i = 0;
	if (ft_isalpha(input[0]) == 0 && input[0] != '_')
	{
		printf("export: '%s': not a valid identifier\n", input);
		return (NULL);
	}
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	if (input[i] == '=' || input[i] == '\0' || input[i] == ' ' \
		|| input[i] == '"' || input[i] == '$')
		key = ft_substr(input, 0, i);
	else
		key = NULL;
	return (key);
}

/**
 * find_value - Extracts the value from the input string (key-value pair).
 *
 * @param input   The input string containing the key-value pair.
 * @return        The extracted value.
 */
char	*find_value(char *input)
{
	return (ft_substr(input, ft_strchr(input, '=') \
					- input + 1, ft_strlen(input) - \
					(ft_strchr(input, '=') - input)));
}
