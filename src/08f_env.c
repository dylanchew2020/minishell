/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08f_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:10 by lchew             #+#    #+#             */
/*   Updated: 2023/08/02 14:14:44 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env(t_list **env_list)
{
	t_env	*data;
	t_list	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		data = (t_env *)tmp->content;
		if (data->value != NULL)
			printf("%s=%s\n", data->key, data->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	env_link_list(char **envp, t_list **env_list)
{
	int		i;
	t_env	*content;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		content = ft_calloc(1, sizeof(t_env));
		if (!content)
			return (EXIT_FAILURE);
		content->key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		content->value = ft_substr(envp[i], \
						ft_strchr(envp[i], '=') - envp[i] + 1, \
						ft_strlen(envp[i]) - \
						(ft_strchr(envp[i], '=') - envp[i]));
		node = ft_lstnew(content);
		ft_lstadd_back(env_list, node);
		i++;
	}
	return (EXIT_SUCCESS);
}

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
		if (ft_strncmp(data->key, key, ft_strlen(key) + 1) == 0)
		{
			value = data->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (value);
}

void	creat_new_env_node(char *key, char	*input, t_list **env_list)
{
	t_env	*data;
	t_list	*node;
	char	*equal_ptr;

	data = ft_calloc(1, sizeof(t_env));
	equal_ptr = ft_strchr(input, '=');
	data->key = ft_substr(key, 0, ft_strlen(key));
	data->value = NULL;
	if (equal_ptr != NULL)
		data->value = ft_substr(input, equal_ptr - input + 1, \
							ft_strlen(input) - (equal_ptr - input));
	node = ft_lstnew(data);
	ft_lstadd_back(env_list, node);
}
