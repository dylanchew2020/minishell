/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:50:10 by lchew             #+#    #+#             */
/*   Updated: 2022/05/25 16:50:10 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_substr - Allocates (with malloc(3)) and returns a substring from 
 *             the string 's'. The substring begins at index 'start' and 
 *             is of maximum size 'len'.
 * @param s: The string from which to create the substring.
 * @param start: The start index of the substring in the string 's'.
 * @param len: The maximum length of the substring.
 * 	
 * @returns 
 * The substring. NULL if the allocation fails or if 's' is NULL. 
 * If start is greater than the length of 's', the function will 
 * return an empty string.
 * If the length of 's' from the 'start' index is less than 'len', 
 * the substring will only be as long as the remaining length of 's'.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			i;

	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	s += start;
	i = ft_strlen(s);
	if (i < len)
		len = i;
	sub = ft_calloc((len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s, len + 1);
	return (sub);
}
