/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:03 by lchew             #+#    #+#             */
/*   Updated: 2023/07/20 20:55:44 by lchew            ###   ########.fr       */
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

int	heredoc_fd(char *node_value, t_root *sh)
{
	char	*delim;
	int		fd;
	char	*line;
	char	*tmp;

	delim = find_file(node_value);
	if (delim == NULL)
	{
		ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if (access(".here_doc_tmp", F_OK & X_OK) == 0)
		unlink(".here_doc_tmp");
	fd = ft_open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (TRUE)
	{
		if (sh->pipe[1] != 0)
		{
			ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
			line = readline("> ");
			ft_dup2(sh->pipe[1], STDOUT_FILENO);
		}
		else
			line = readline("> ");
		if (line == NULL)
		{
			free(delim);
			free(line);
			return (-2);
		}
		if ((ft_strlen(line) == ft_strlen(delim)) \
		&& ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			ft_close(fd);
			break ;
		}
		tmp = line;
		line = expand(line, &sh->env_list);
		free(tmp);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (access(".here_doc_tmp", F_OK & X_OK) != 0)
	{
		printf("Error: %s: %s\n", strerror(errno), ".here_doc_tmp");
		free(delim);
		return (-1);
	}
	fd = ft_open(".here_doc_tmp", O_RDONLY, 0666);
	free(delim);
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
		return (NULL); // change to if statement, check for correct redir token
	while ((*value == '<' || *value == '>' || *value == ' ') && *value != '\0')
		++value;
	if (*value == '\0')
		return (NULL);
	result = cmd_quote_handler(value, ' ');
	file = ft_strdup(result[0]);
	free_2d(result);
	return (file);
}
