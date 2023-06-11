/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:52:57 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/06/11 17:04:52 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * complete_path - Appends a slash at the end of each string in the path array.
 * @param path: The array of strings.
 */
static void	complete_path(char **path)
{
	int		i;
	char	*temp;

	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		if (temp != NULL)
		{
			free(path[i]);
			path[i] = temp;
		}
		else
		{
			printf("Error: %s\n", strerror(errno));
			return ;
		}
	}
}

/**
 * find_path - Finds the system PATH, splits it into separate directories, 
 *             and appends a slash at the end of each directory.
 * @param void
 *
 * @returns 
 * An array of strings, each string being a directory from the system PATH, 
 * or NULL if PATH is not found or an error occurs.
 */
char	**find_path(void)
{
	char	*tmp;
	char	**path;

	tmp = getenv("PATH");
	if (tmp != NULL)
	{
		path = ft_split(tmp, ':');
		complete_path(path);
		return (path);
	}
	printf("Error: %s\n", strerror(errno));
	return (NULL);
}
