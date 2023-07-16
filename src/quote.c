/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:04 by lchew             #+#    #+#             */
/*   Updated: 2023/07/15 16:50:20 by tzi-qi           ###   ########.fr       */
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
		++count;
		++cmd;
	}
	++count;
	return (count);
}

// char	*cmd_quote_handler(char *cmd, int *i, int *j)
// {
// 	int		quote_type;
// 	int		quote_len;
// 	char	*quoted_str;

// 	quote_type = is_quote(cmd[*i]);
// 	quote_len = quote_count(&cmd[*i]);
// 	if (quote_len == -1)
// 		return (NULL);
// 	quoted_str = ft_substr(cmd, *i + 1, quote_len - 1);
// 	if (!quoted_str)
// 		return (NULL);
// 	*i += quote_len + 1;
// 	*j += quote_len;
// 	return (quoted_str);
// }

static int	countstr(char const *s, char c)
{
	int	count;
	int	quote_len;

	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			++count;
			quote_len = quote_count((char *)s);
			while ((quote_len > 0 || *s != c) && *s != '\0')
			{
				s += quote_len;
				quote_len = 0;
				if (is_quote(*s) != 0)
					quote_len = quote_count((char *)s);
				else if (*s != '\0')
					++s;
			}
		}
		else
			++s;
	}
	return (count);
}

static char	*nextstr(char const **s, char c)
{
	char	*start;
	char	*str;
	int		quote_len;
	int		str_len;
	int		i;
	int		j;
	int		quote_type;

	str_len = 0;
	while (**s == c)
		++(*s);
	start = (char *)*s;
	quote_len = quote_count((char *)s);
	while ((quote_len > 0 || **s != c) && **s != '\0')
	{
		*s += quote_len;
		str_len += quote_len;
		quote_len = 0;
		if (is_quote(**s) != 0)
			quote_len = quote_count((char *)*s);
		else if (**s != '\0')
		{
			++(*s);
			++str_len;
		}
	}
	str = ft_substr(start, 0, str_len);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		quote_type = is_quote(str[i]);
		if (quote_type != 0)
		{
			++i;
			while (is_quote(str[i]) != quote_type)
				str[j++] = str[i++];
			++i;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (str);
}

char	**cmd_quote_handler(char const *s, char c)
{
	char	**res;
	int		i;
	int		n;

	if (s == NULL)
		return (NULL);
	n = countstr(s, c);
	res = ft_calloc(n + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < n)
	{
		res[i] = nextstr(&s, c);
		if (!res[i])
		{
			while (i > 0)
				free(res[--i]);
			free(res);
			return (NULL);
		}
		++i;
	}
	return (res);
}