/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:04 by lchew             #+#    #+#             */
/*   Updated: 2023/07/29 16:19:02 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				else if (*s != ' ' && *s != '\0')
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

	str_len = 0;
	while (**s == c)
		++(*s);
	start = (char *)*s;
	quote_len = quote_count((char *)*s);
	while ((quote_len > 0 || **s != c) && **s != '\0')
	{
		*s += quote_len;
		str_len += quote_len;
		quote_len = 0;
		if (is_quote(**s) != 0)
			quote_len = quote_count((char *)*s);
		else if (**s != c && **s != '\0')
		{
			++(*s);
			++str_len;
		}
	}
	str = ft_substr(start, 0, str_len);
	return (remove_quote(str));
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
	i = 0;
	while (i < n)
	{
		res[i] = nextstr(&s, c);
		if (!res[i])
		{
			free_2d(res);
			return (NULL);
		}
		++i;
	}
	return (res);
}

// void	**cmd_join_utils(char ***res, char ***new_res, char ***add_arg)
// {
// 	char	**r;
// 	char	**n;
// 	char	**a;
// 	int		i;
// 	int		j;

// 	r = *res;
// 	n = *new_res;
// 	a = *add_arg;
// }

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
	i = 0;
	while (res[i] != NULL)
	{
		new_res[i] = ft_strdup(res[i]);
		if (!new_res[i])
		{
			free_2d(new_res);
			return (NULL);
		}
		++i;
	}
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
	free_2d(res);
	free_2d(add_arg);
	return (new_res);
}
