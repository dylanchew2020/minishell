/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:04 by lchew             #+#    #+#             */
/*   Updated: 2023/06/03 17:25:26 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

int	quote_count(char *cmd)
{
	int	count;
	int	quote_type;

	quote_type = is_quote(*cmd++);
	if (!cmd || quote_type == 0)
		return (0);
	count = 1;
	while (is_quote(*cmd) != quote_type)
	{
		if (*cmd == '\0')
		{
			ft_putstr_fd("Error: unclosed quote.\n", STDERR_FILENO);
			return (-1);
		}
		count++;
		cmd++;
	}
	return (count);
}
