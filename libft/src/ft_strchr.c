/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:01:55 by lchew             #+#    #+#             */
/*   Updated: 2022/05/23 21:01:55 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strchr - Locates the first occurrence of 'c' in string 's'.
 * @param s: The string to be scanned.
 * @param c: The character to be located.
 *
 * @returns
 * A pointer to the first occurrence of 'c' in 's',
 * or NULL if 'c' is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	if (c >= 256)
		c -= 256;
	while (*s != '\0' && *s != c)
		++s;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
