/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:52:57 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/22 17:51:23 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends a "/" to the end of each string in a path array.
 *
 * This function modifies the array in place. It prints an error message and
 * returns if an error occurs during memory allocation.
 *
 * @param path An array of strings representing paths.
 */
static void	path_helper(char **path)
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
 * @brief Finds the system PATH.
 *
 * This function splits the PATH environment variable into an array of
 * strings, adds a "/" to the end of each path, and returns the array.
 *
 * @return An array of strings representing the system PATH, or NULL if an
 * error occurs.
 */
char	**find_path(void)
{
	char	*tmp;
	char	**path;

	tmp = getenv("PATH");
	if (tmp != NULL)
	{
		path = ft_split(tmp, ':');
		path_helper(path);
		return (path);
	}
	printf("Error: %s\n", strerror(errno));
	return (NULL);
}

/**
 * @brief Determines the full path of an executable given its name.
 *
 * Splits the provided command into words, checks if any of the path 
 * strings stored in PATH match the command name, then joins the path
 * with the command if a match is found and the file exists.
 *
 * @param argv The command to find the path for.
 * @return The full path of the executable if found, NULL otherwise.
 */
char	*get_exe_path(char *argv)
{
	char	*cmd;
	char	**tmp;
	char	*join;
	int		i;

	tmp = ft_split(argv, ' ');
	cmd = ft_strdup(tmp[0]);
	free_2d(tmp);
	tmp = find_path();
	i = -1;
	while (tmp[++i])
	{
		if (ft_strncmp(tmp[i], cmd, ft_strlen(tmp[i])) == 0)
		{
			free_2d(tmp);
			return (cmd);
		}
		join = ft_strjoin(tmp[i], cmd);
		if (access(join, F_OK) == 0)
		{
			free (cmd);
			free_2d(tmp);
			return (join);
		}
		free(join);
	}
	free (cmd);
	free_2d(tmp);
	return (NULL);
}
