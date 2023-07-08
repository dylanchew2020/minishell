/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:04 by lchew             #+#    #+#             */
/*   Updated: 2023/07/08 14:48:52 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a character is a quote.
 * 
 * @param c The character to check.
 * @return 1 if it's a single quote, 2 if it's a double quote,
 * or 0 otherwise.
 */
int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

/**
 * @brief Counts the length of the quoted string in a command.
 * 
 * Checks the type of quote at the start and counts characters 
 * until the closing quote. If a null character is encountered 
 * before finding a closing quote, an error message is output.
 *
 * @param cmd The command string.
 * @return The length of the quoted string, or 0 if no quote at 
 * the start. -1 if an unclosed quote is found.
 */
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
