/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07a_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:03 by lchew             #+#    #+#             */
/*   Updated: 2023/08/02 14:48:03 by lchew            ###   ########.fr       */
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
int	rdin_fd(char *node_value, t_root *sh)
{
	char	*file;
	int		fd;

	file = find_file(node_value);
	if (file == NULL)
	{
		ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if (access(file, F_OK & X_OK) != 0)
	{
		ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
		printf("Error: %s: %s\n", strerror(errno), file);
		free(file);
		return (-2);
	}
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
int	rdout_fd(char *node_value, t_root *sh)
{
	char	*file;
	int		fd;

	file = find_file(node_value);
	if (file == NULL)
	{
		ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	fd = ft_open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	free(file);
	return (fd);
}

int	rdapp_fd(char *node_value, t_root *sh)
{
	char	*file;
	int		fd;

	file = find_file(node_value);
	if (file == NULL)
	{
		ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	fd = ft_open(file, O_CREAT | O_RDWR | O_APPEND, 0666);
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
	char	**result;
	char	*file;

	if ((*value != '<' && *value != '>') && *value != '\0')
		return (NULL);
	while ((*value == '<' || *value == '>' || *value == SPACE) \
			&& *value != '\0')
		++value;
	if (*value == '\0')
		return (NULL);
	result = cmd_quote_handler(value, SPACE);
	file = ft_strdup(result[0]);
	free_2d(result);
	return (file);
}
