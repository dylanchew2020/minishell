/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05a_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:21:02 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/30 16:24:14 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	join_first_cmd(char **new_res, char **res);
static char	**join_second_cmd(char **new_res, char **add_arg, int i);

char	**cmd_join(char **res, t_root *sh)
{
	int		i;
	int		j;
	char	**new_res;
	char	**add_arg;

	i = 0;
	j = 0;
	add_arg = cmd_quote_handler(sh->tree_arg_value, ' ');
	while (res[i] != NULL)
		++i;
	while (add_arg[j] != NULL)
		++j;
	new_res = ft_calloc(i + j + 1, sizeof(char *));
	i = join_first_cmd(new_res, res);
	free_2d(res);
	if (i == -1)
		return (NULL);
	return (join_second_cmd(new_res, add_arg, i));
}

static int	join_first_cmd(char **new_res, char **res)
{
	int	i;

	i = 0;
	i = 0;
	while (res[i] != NULL)
	{
		new_res[i] = ft_strdup(res[i]);
		if (!new_res[i])
		{
			free_2d(new_res);
			return (-1);
		}
		++i;
	}
	return (i);
}

static char	**join_second_cmd(char **new_res, char **add_arg, int i)
{
	int		j;

	j = 0;
	while (add_arg[j] != NULL)
	{
		new_res[i] = ft_strdup(add_arg[j]);
		if (!new_res[i])
		{
			free_2d(new_res);
			return (NULL);
		}
		++i;
		++j;
	}
	free_2d(add_arg);
	return (new_res);
}