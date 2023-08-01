/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08d_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:26:43 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/01 23:20:41 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_declare(t_list **env_list);
static void	modified_value(t_env *data_node, char *input);
static int	add_link_list(char	*input, t_list	**env_list);

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
			if (ft_strchr(split[i], '=') != NULL)
				if (add_link_list(split[i], env_list) == 1)
					return (EXIT_FAILURE);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

static void	export_declare(t_list **env_list)
{
	t_list	*tmp;
	t_env	*data;

	tmp = *env_list;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		printf("declare -x %s=\"%s\"\n", data->key, data->value);
		tmp = tmp->next;
	}
}

static void	modified_value(t_env *data_node, char *input)
{
	char	*value;
	char	*tmp;

	value = ft_substr(input, ft_strchr(input, '=') \
					- input + 1, ft_strlen(input) - \
					(ft_strchr(input, '=') - input));
	tmp = data_node->value;
	data_node->value = value;
	free(tmp);
}

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

int	invalid_identifier(char *input)
{
	char	*start;
	char	*equal_ptr;

	start = input;
	equal_ptr = ft_strchr(input, '=');
	while (input < equal_ptr)
	{	
		if ((ft_isalpha(*input) == 0 && *input != '_'))
		{
			printf("export 1: '%s': not a valid identifier\n", start);
			g_exit_status = 1;
			return (EXIT_FAILURE);
		}
		++input;
	}
	return (EXIT_SUCCESS);
}
