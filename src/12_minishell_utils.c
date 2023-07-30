/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_minishell_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:00:27 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/30 17:32:24 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_pipe - Creates a pipe between two file descriptors. If the pipe cannot
 *           be created, it outputs an error message and terminates the
 *           process with an exit status of 1.
 *
 * @param p: A two-element array to hold the file descriptors for the input
 *           and output ends of the pipe.
 *
 * @returns
 * The file descriptor for the input end of the pipe, or terminates the
 * process if the pipe could not be created.
 */
int	ft_pipe(int p[2])
{
	if (pipe(p) == -1)
	{
		printf("pipe: %d\n", getpid());
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (*p);
}

/**
 * ft_open - Opens a file with the given flags and permissions. If the file
 *           cannot be opened, it outputs an error message and terminates the
 *           process with an exit status of 1.
 *
 * @param file: The name of the file to be opened.
 * @param flags: The flags to use when opening the file.
 * @param permission: The permissions to use when opening the file.
 *
 * @returns
 * The file descriptor for the opened file, or terminates the process if
 * the file could not be opened.
 */
int	ft_open(const char *file, int flags, int permission)
{
	int	fd;

	fd = open(file, flags, permission);
	if (fd < 0)
	{
		printf("open: %d\n", getpid());
		ft_putstr_fd("Error: Failed to open file\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * ft_fork - Forks a new child process. If the fork cannot be completed,
 *           it outputs an error message and terminates the process
 *           with an exit status of 1.
 *
 * @returns
 * The PID of the child process, or terminates the process if the
 * fork could not be completed.
 */
int	ft_fork(void)
{
	pid_t	child;

	child = fork();
	if (child < 0)
	{
		printf("fork: %d\n", getpid());
		ft_putstr_fd("Error: Failed to create child process\n", 2);
		exit(1);
	}
	return (child);
}

/**
 * ft_close - Closes a file descriptor. If the file descriptor cannot be
 * 			  closed, it outputs an error message and terminates the
 * 			  process with an exit status of 1.
 *
 * @param fd: The file descriptor to close.
 *
 * @returns
 * 0 on successful closure, or terminates the process if the closure could
 * not be completed.
 */
int	ft_close(int fd)
{
	if (close(fd) < 0)
	{
		printf("close: %d\n", getpid());
		ft_putstr_fd("Error: Failed to close the fd\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * ft_dup2 - Duplicates a file descriptor, replacing an old file descriptor
 * 			 with a new one. If the file descriptor cannot be duplicated,
 * 			 it outputs an error message and terminates the process with
 * 			 an exit status of 1.
 *
 * @param new_fd: The new file descriptor.
 * @param old_fd: The old file descriptor to be replaced.
 *
 * @returns
 * The new file descriptor on successful duplication, or terminates the process
 * if the duplication could not be completed.
 */
int	ft_dup2(int new_fd, int old_fd)
{
	int	i;

	i = dup2(new_fd, old_fd);
	if (i < 0)
	{
		printf("Error: Failed to dup2\n");
		exit(EXIT_FAILURE);
	}
	return (i);
}
