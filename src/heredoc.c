/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:50:58 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/26 18:17:07 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * heredoc_fd - to check whether the redirect in file exists or not.
 *  		if "infile" do not exist, exit with error message.
 * 			else return the file descriptor of the file.
 * @param path: node->value
 * @returns fd: file descriptor of the infile.
 */
int	heredoc_fd(char *node_value, t_root *sh)
{
	char	*delim;
	int		fd;
	pid_t	child;

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
	child = ft_fork();
	if (child == 0)
		heredoc_child(sh, delim, fd);
	else
		fd = heredoc_parent(child, delim);
	return (fd);
}

char	*heredoc_input(t_root *sh, char *delim)
{
	char	*line;

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
		exit(-1);
	}
	return (line);
}

void	heredoc_child(t_root *sh, char *delim, int heredoc_fd)
{
	char	*line;
	char	*tmp;

	while (TRUE)
	{
		signals(sh, 2);
		line = heredoc_input(sh, delim);
		if ((ft_strlen(line) == ft_strlen(delim)) \
		&& (ft_strncmp(line, delim, ft_strlen(delim)) == 0))
		{
			free(line);
			ft_close(heredoc_fd);
			break ;
		}
		tmp = line;
		line = expand(line, &sh->env_list);
		free(tmp);
		ft_putstr_fd(line, heredoc_fd);
		ft_putstr_fd("\n", heredoc_fd);
		free(line);
	}
	free(delim);
	exit(EXIT_SUCCESS);
}

int	heredoc_parent(pid_t child_pid, char *delim)
{
	int	fd;
	int	status;

	signal(SIGQUIT, SIG_IGN);
	waitpid(child_pid, &status, 0);
	status = WEXITSTATUS(status);
	free(delim);
	if (status == 255)
		return (-1);
	if (access(".here_doc_tmp", F_OK & X_OK) != 0)
	{
		printf("Error: %s: %s\n", strerror(errno), ".here_doc_tmp");
		return (-1);
	}
	fd = ft_open(".here_doc_tmp", O_RDONLY, 0666);
	return (fd);
}
