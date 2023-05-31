/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/05/31 17:52:01 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char	**envp, char **argv)
{
	char *line;
	(void)argv;
	char **path;
	int i = -1;

	path = find_path(envp);
	while (path[++i])
		printf("%s\n", path[i]);
	while (1)
	{
		// write(1, "MINISHELL>>", 11);
		line = readline("MINISHELL: ");
		if (line && *line)
		{
			// add_history(line);
			printf("%s\n", line);
		}
		free(line);
	}
	return ;
}