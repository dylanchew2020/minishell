/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08c_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:30:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/02 17:38:43 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the current working directory.
 *
 * This function retrieves and prints the current working directory to
 * the standard output using the getcwd system call.
 *
 * @return EXIT_SUCCESS if successful, or EXIT_FAILURE if an error occurs.
 */
int	pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd: ");
		return (EXIT_FAILURE);
	}
	else
		printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
