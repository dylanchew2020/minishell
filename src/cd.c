/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:03 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/15 16:54:35 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * cd - Changes the current working directory to the specified directory.
 *
 * @param value Double pointer to a character array containing the directory path.
 *              The directory path is stored in value[1].
 *              Assumes value[0] is the command itself.
 */


void	cd(char **value)
{
	char	**split;
	int		i;

	split = value;
	printf("split[1] = %s\n", split[1]);
	i = chdir(split[1]);
	printf("i = %d\n", i);
	if (i != 0)
		perror("something wrong lah");
	free_2d(split);
}
