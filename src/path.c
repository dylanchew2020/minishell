/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:52:57 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/05/31 19:21:28 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	complete_path(char **split)
{
	int i;
	char *temp;

	i = -1;
	while(split[++i])
	{
		temp = ft_strjoin(split[i], "/");
		free(split[i]);
		split[i] = temp;
	}
}

char	**find_path(char **envp)
{
	char *path;
	char **split;
	(void)envp;

	path = getenv("PATH");
	if (path != NULL)
	{
		path = ft_substr(path, 5, ft_strlen(path));
		split = ft_split(path, ':');
		complete_path(split);
		free(path);
		return (split);
	}
	if (path == NULL)
		printf("Error: %s\n", strerror(errno));
	return (NULL);
}

void check_path