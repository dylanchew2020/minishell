/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08d_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:26:43 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/01 21:38:32 by lchew            ###   ########.fr       */
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
			if ((ft_isalpha(split[i][0]) == 0 && split[i][0] != '_') || \
				ft_strchr(split[i], ' ') != NULL)
			{
				printf("export 1: '%s': not a valid identifier\n", split[i]);
				g_exit_status = 1;
				return (EXIT_FAILURE);
			}
			if (ft_strchr(split[i], '=') != NULL)
				if (add_link_list(split[i], env_list) != 0)
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
	printf("key: |%s| %p\n", key, key);
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
	return (EXIT_SUCCESS);
}

char	*key_check(char *input)
{
	int		i;
	char	*key;

	i = 0;
	printf("input: |%s| %p\n", input, input);
	printf("input space: %p\n", ft_strchr(input, ' '));
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	if (i == 0)
		key = NULL;
	else
		key = ft_substr(input, 0, i);
	return (key);
}
