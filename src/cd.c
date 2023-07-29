/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:03 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/22 16:46:55 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tilda_helper(char **dir, t_list **env_list);

/**
 * @brief Changes the current working directory.
 *
 * Changes the working directory to the value specified. If no value is
 * provided, changes to the directory specified by the "HOME" environment
 * variable.
 *
 * @param value An array containing the command and its arguments.
 * @param env_list Pointer to the environment list.
 */
void	cd(char **value, t_list **env_list)
{
	char	**split;
	int		i;

	split = NULL;
	if (value[1] == NULL)
	{
		if (existed_env("HOME", env_list) == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return ;
		}
		i = chdir(existed_env("HOME", env_list));
	}
	else
	{
		split = value;
		tilda_helper(&split[1], env_list);
		i = chdir(split[1]);
		if (i != 0)
			perror("cd: ");
	}
}

/**
 * @brief Replaces a tilde (~) in the directory string with the value of HOME.
 *
 * The tilde is only replaced if it appears at the start of the string,
 * before any slash (/). If a tilde appears after a slash, it is not replaced.
 *
 * @param dir Pointer to the directory string.
 * @param env_list Pointer to the environment list.
 */
static void	tilda_helper(char **dir, t_list **env_list)
{
	char	*tilda_ptr;
	char	*slash_ptr;
	char	*tmp;

	slash_ptr = ft_strchr(*dir, '/');
	tilda_ptr = ft_strchr(*dir, '~');
	if (tilda_ptr != NULL && slash_ptr == NULL)
	{
		free(*dir);
		*dir = ft_strdup(existed_env("HOME", env_list));
	}
	else if (tilda_ptr != NULL && tilda_ptr < slash_ptr) 
	{
		tmp = *dir;
		*dir = ft_strjoin(existed_env("HOME", env_list), slash_ptr);
		free(tmp);
	}
}

