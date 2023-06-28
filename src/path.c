/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:52:57 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/06/28 18:42:27 by tzi-qi           ###   ########.fr       */
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

/**
 * the_legit_path - Find the path for the command
 * @param argv : the cmmand argument including flag
 * 					option
 * @returns 
 * A string that contained the PATH of the command, 
 * or NULL if PATH is not found or an error occurs.
 */
char	*the_legit_path(char *argv)
{
	char	*cmd;
	char	**path;
	char	*join;
	int		i;

	path = ft_split(argv, ' ');
	cmd = ft_strdup(path[0]);
	free_2d(path);
	path = find_path();
	i = -1;
	while (path[++i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, F_OK) == 0)
		{
			free (cmd);
			free_2d(path);
			return (join);
		}
		free(join);
	}
	free (cmd);
	free_2d(path);
	return (NULL);
}
