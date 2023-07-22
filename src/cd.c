/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:03 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/22 16:24:11 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tilda_helper(char **dir, t_list **env_list);

/**
 * cd - Changes the current working directory to the specified directory.
 *
 * @param value Double pointer to a character array containing the directory path.
 *              The directory path is stored in value[1].
 *              Assumes value[0] is the command itself.
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
		printf("split[1] = %s\n", split[1]);
		i = chdir(split[1]);
		printf("i = %d\n", i);
		if (i != 0)
			perror("cd: ");
		free_2d(split);
	}
}

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

