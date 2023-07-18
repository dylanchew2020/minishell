/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:10 by lchew             #+#    #+#             */
/*   Updated: 2023/07/13 15:52:14 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * env_link_list - Converts the environment variables array into a linked list.
 *                 Each node in the linked list represents an environment variable.
 *
 * @param envp     Double pointer to an array of strings containing the environment variables.
 *                 The environment variables are expected to be in the format "key=value".
 * @param env_list Double pointer to a linked list where the environment variables will be stored.
 *                 Assumes env_list is initially empty (NULL).
 */

void	env_link_list(char **envp, t_list **env_list)
{
	int		i;
	t_env	*content;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		content = ft_calloc(1, sizeof(t_env));
		content->key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		content->value = ft_substr(envp[i], \
						ft_strchr(envp[i], '=') - envp[i] + 1, \
						ft_strlen(envp[i]) - \
						(ft_strchr(envp[i], '=') - envp[i]));
		node = ft_lstnew(content);
		ft_lstadd_back(env_list, node);
		i++;
	}
}

/**
 * get_env - Prints the key-value pairs of the environment variables stored in the linked list.
 *
 * @param env_list Double pointer to the linked list containing the environment variables.
 */

void	get_env(t_list **env_list)
{
	t_env	*data;
	t_list	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		printf("%s=%s\n", data->key, data->value);
		tmp = tmp->next;
	}
}

/**
 * existed_env - Retrieves the value of an environment variable by its key.
 *
 * @param key       Key of the environment variable to search for.
 * @param env_list  Double pointer to the linked list containing the environment variables.
 * @return          Value of the environment variable if found, or NULL if not found.
 */
char	*existed_env(char *key, t_list **env_list)
{
	char	*value;
	t_env	*data;
	t_list	*tmp;

	if (key == NULL)
		return (NULL);
	value = NULL;
	tmp = *env_list;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		if (ft_strncmp(data->key, key, ft_strlen(key)) == 0)
		{
			value = data->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (value);
}

/**
 * creat_new_env_node - Creates a new node for an environment variable and adds it to the linked list.
 *
 * @param key       Key of the new environment variable.
 * @param input     Input string containing the value of the new environment variable.
 * @param env_list  Double pointer to the linked list where the new environment variable will be added.
 */
void	creat_new_env_node(char *key, char	*input, t_list **env_list)
{
	t_env	*data;
	t_list	*node;

	printf("creating new node\n");
	data = ft_calloc(1, sizeof(t_env));
	data->key = key;
	data->value = find_value(input);
	node = ft_lstnew(data);
	ft_lstadd_back(env_list, node);
}
