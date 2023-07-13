/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:03 by lchew             #+#    #+#             */
/*   Updated: 2023/07/13 14:09:55 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(file);
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
	free(file);
	return (fd);
}

int	rdapp_fd(char *node_value)
{
	char	*file;
	int		fd;

	file = find_file(node_value);
	fd = ft_open(file, O_CREAT | O_RDWR | O_APPEND, 0666);
	free(file);
	return (fd);
}

int	heredoc_fd(char *node_value)
{
	char	*file;
	int		fd;

	file = find_file(node_value);
	fd = ft_open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	free(file);
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
		++value;
	while ((*value == '<' || *value == '>') && *value != '\0')
		++value;
	return (ft_strtrim(value, " "));
}
