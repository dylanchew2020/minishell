/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utlis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:00:27 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/06/14 19:26:57 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(int p[2])
{
	if (pipe(p) < 0)
	{
		printf("pipe: %d\n", getpid());
		ft_putstr_fd("Error: can't create a pipe \n", 2);
		exit (1);
	}
	return (*p);
}

int	ft_open(const char *file, int flags, int permission)
{
	int	fd;

	fd = open(file, flags, permission);
	if (fd < 0)
	{
		printf("open: %d\n", getpid());
		ft_putstr_fd("Error: Can't open file\n", 2);
		exit (1);
	}
	return (fd);
}

int	ft_fork(void)
{
	pid_t	child;

	child = fork();
	if (child < 0)
	{
		printf("fork: %d\n", getpid());
		ft_putstr_fd("Error: Can't fork a child\n", 2);
		exit (1);
	}
	return (child);
}

int	ft_close(int fd)
{
	if (close(fd) < 0)
	{
		printf("close: %d\n", getpid());
		ft_putstr_fd("Error: Can't close the fd\n", 2);
		exit (1);
	}
	return (0);
}

int	ft_dup2(int new_fd, int old_fd)
{
	int i;

	i = dup2(new_fd, old_fd);
	if (i < 0)
		exit(printf("Error: Can't dup2\n"));
	return (i);
}
