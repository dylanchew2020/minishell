/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:26:43 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/05 20:27:22 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

//detext for "="
//else do nothing
//get the key from the head node->value
//get the value 
// put it into link list
//ft_lstadd back

int	 error_check(char *str);

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
			// if (error_check(split[i]) == 0)
			// 	break ;
			if (ft_isalpha(split[i][0]) == 0 && split[i][0] != '_')
				printf("export: '%s': not a valid identifier\n", split[i]);
			// printf("|%s|\n", split[i]);
			i++;
		}
	}
}

int	error_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%c\n", str[i]);
		if (str[i] == '=')
			break ;
		if (ft_isalpha(str[i]) == 0)
		{
			printf("export: '%s': not a valid identifier\n", str);
			break ;
		}
		i++;
	}
	if (str[i] == '=')
		return (1);
	else
		return (0);
}
