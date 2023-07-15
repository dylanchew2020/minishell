/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:03 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/08 16:54:05 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	cd(char *value)
{
	char	**split;

	split = ft_split(value, ' ');
	if (chdir(split[1]) != 0)
		perror("something wrong lah");
	free_2d(split);
}
