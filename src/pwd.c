/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:30:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/08 16:33:01 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/**
 * pwd - Prints the current working directory.
 */
void	pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n",cwd);
}
