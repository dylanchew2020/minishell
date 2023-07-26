/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:52:57 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/26 18:55:30 by tzi-qi           ###   ########.fr       */
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
			printf("Error: Path Helper Failed: %s\n", strerror(errno));
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
char	**find_path(t_list **env_list)
{
	char	*tmp;
	char	**path;

	tmp = existed_env("PATH", env_list);
	if (tmp != NULL)
	{
		path = ft_split(tmp, ':');
		path_helper(path);
		return (path);
	}
	return (NULL);
}

static char	*join_path_helper(char *cmd, char **tmp, int i)
{
	char	*join;

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
	return (NULL);
}

char	*join_path(t_list **env_list, char *cmd)
{
	char	**tmp;
	char	*join;
	int		i;

	tmp = find_path(env_list);
	if (tmp == NULL)
	{
		free(cmd);
		return (NULL);
	}
	i = -1;
	while (tmp[++i])
	{
		join = join_path_helper(cmd, tmp, i);
		if (join != NULL)
			return (join);
	}
	free (cmd);
	free_2d(tmp);
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
char	*get_exe_path(char *argv, t_list **env_list)
{
	char	*cmd;
	char	*join;

	cmd = ft_strdup(argv);
	if (strncmp(cmd, "./", 2) == 0 || strncmp(cmd, "../", 3) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			free(cmd);
			return (NULL);
		}
	}
	join = join_path(env_list, cmd);
	if (join != NULL)
		return (join);
	return (NULL);
}
