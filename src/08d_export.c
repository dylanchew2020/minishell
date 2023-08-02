/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08d_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:26:43 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/02 17:10:56 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_declare(t_list **env_list);
static void	modified_value(t_env *data_node, char *input);
static int	add_link_list(char	*input, t_list	**env_list);

/**
 * export - Handles the export command in the shell.
 *
 * @param cmd: A pointer to the command string.
 * @param env_list: A double pointer to the linked list of environment variables.
 *
 * @returns EXIT_SUCCESS on success or EXIT_FAILURE on failure.
 */
int	export(char **cmd, t_list **env_list)
{
	char	**split;
	int		i;

	i = 1;
	split = cmd;
	if (split[1] == NULL)
	{
		export_declare(env_list);
		return (EXIT_SUCCESS);
	}
	else
	{
		while (split[i])
		{
			if (invalid_identifier(split[i]) == 1)
				return (EXIT_FAILURE);
			else
				if (add_link_list(split[i], env_list) == 1)
					return (EXIT_FAILURE);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * export_declare - Prints all current environment variables in the
 * 					 "declare -x" format.
 *
 * @param env_list: A double pointer to the linked list of environment variables.
 */
static void	export_declare(t_list **env_list)
{
	t_list	*tmp;
	t_env	*data;

	tmp = *env_list;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		if (data->value == NULL)
			printf("declare -x %s\n", data->key);
		else
			printf("declare -x %s=\"%s\"\n", data->key, data->value);
		tmp = tmp->next;
	}
}

/**
 * modified_value - Modifies the value of an existing environment variable.
 *
 * @param data_node: Pointer to the environment variable's data node.
 * @param input: The new value to set for the environment variable.
 */
static void	modified_value(t_env *data_node, char *input)
{
	char	*value;
	char	*tmp;
	char	*equal_ptr;

	equal_ptr = ft_strchr(input, EQUAL);
	value = ft_substr(input, equal_ptr - input + 1, \
						ft_strlen(input) - (equal_ptr - input));
	tmp = data_node->value;
	data_node->value = value;
	free(tmp);
}

/**
 * add_link_list - Adds or updates an environment variable in the linked list.
 *
 * @param input: The input string containing the environment variable key 
 * 				 and value.
 * @param env_list: A double pointer to the linked list of environment variables.
 *
 * @returns EXIT_SUCCESS on success or EXIT_FAILURE on failure.
 */
static int	add_link_list(char	*input, t_list	**env_list)
{
	char	*key;
	t_env	*data;
	t_list	*tmp;
	int		i;

	key = key_check(input);
	if (key == NULL)
		return (EXIT_FAILURE);
	tmp = *env_list;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		i = ft_strncmp(data->key, key, ft_strlen(data->key) + 1);
		if (i == 0)
		{
			if (ft_strchr(input, EQUAL) != NULL)
				modified_value(data, input);
			break ;
		}
		tmp = tmp->next;
	}
	if (i != 0)
		creat_new_env_node(key, input, env_list);
	free(key);
	return (EXIT_SUCCESS);
}

/**
 * invalid_identifier - Validates the identifier format of an environment 
 * 						variable.
 *
 * @param input: The input string containing the environment variable key.
 *
 * @returns EXIT_SUCCESS if the identifier is valid, or EXIT_FAILURE if invalid.
 */
int	invalid_identifier(char *input)
{
	char	*start;
	char	*equal_ptr;

	start = input;
	equal_ptr = ft_strchr(input, EQUAL);
	if (start == equal_ptr || (ft_isalpha(*start) == 0 && *start != '_'))
	{
		printf("export 1: '%s': not a valid identifier\n", start);
		g_exit_status = 1;
		return (EXIT_FAILURE);
	}
	while (input < equal_ptr)
	{	
		if (ft_isalnum(*input) == 0 && *input != '_')
		{
			printf("export 1: '%s': not a valid identifier\n", start);
			g_exit_status = 1;
			return (EXIT_FAILURE);
		}
		++input;
	}
	return (EXIT_SUCCESS);
}
