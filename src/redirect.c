/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:03 by lchew             #+#    #+#             */
/*   Updated: 2023/06/19 21:04:51 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		rdin_fd(char *node_value);
int		rdout_fd(char *node_value);
char	*find_file(char *node_value);

/**
 * rdin_fd - to check whether the redirect in file exists or not.
 *  		if "infile" do not exist, exit with error message.
 * 			else return the file descriptor of the file.
 * @param path: node->value
 * @returns fd: file descriptor of the infile.
 */
int	rdin_fd(char *node_value)
{
	char	*file;
	int		fd;

	file = find_file(node_value);
	if (access(file, F_OK & X_OK) != 0)
		exit(printf("Error: %s: %s\n", strerror(errno), file));
	fd = ft_open(file, O_RDONLY, 0666);
	return (fd);
}

/**
 * rdout_fd - check whether the redirect out file exists or not.
 * 					if "outfile" do not exist, create the file.
 * @param path: node->value
 * @returns fd: file descriptor of the outfile.
 */
int	rdout_fd(char *node_value)
{
	char	*file;
	int		fd;

	file = find_file(node_value);
	fd = ft_open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	return (fd);
}

/**
 * find_file - remove the redirection and spaces
 * @param path: the value that stored in node
 * @returns fd: file in char*
 */
char	*find_file(char *value)
{
	while ((*value != '<' && *value != '>') && *value != '\0')
		value++;
	value++;
	return (ft_strtrim(value, " "));
}
