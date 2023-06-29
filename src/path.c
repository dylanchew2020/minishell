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
 * complete_path - Iterates over an array of directory paths, and appends a
 *                 slash ('/') to the end of each path if it does not already
 *                 end with one. This function is useful when the shell is
 *                 searching for executables within directories specified in
 *                 the PATH environment variable.
 *
 * @param path: A pointer to an array of directory paths. The array should be
 *              NULL-terminated.
 *
 * @returns
 * Void. If a memory allocation error occurs during execution, an error message
 * is printed to stdout, but the function does not exit or return any value.
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
 * find_path - Retrieves the PATH environment variable, splits it into an array
 *             of directory paths using colon (':') as a delimiter, and appends
 *             a slash ('/') to the end of each path if it does not already
 *             end with one.
 *
 * @returns
 * A NULL-terminated array of directory paths if successful. Each path ends
 * with a '/'. If PATH is not set, or a memory allocation error occurs during
 * execution, an error message is printed to stdout and NULL is returned.
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
 * the_legit_path - Given a command, this function finds the correct full
 *                  path to the executable file of the command.
 *
 * @param argv: The command to find the path of. The command can be
 *              followed by other arguments, separated by spaces.
 *
 * @returns
 * A string representing the full path to the executable file of the 
 * command, if found. If the command cannot be found in the PATH, or
 * an error occurs during execution, NULL is returned. It is the
 * responsibility of the caller to free the returned string.
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
