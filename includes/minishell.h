/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:28:46 by lchew             #+#    #+#             */
/*   Updated: 2023/05/31 14:46:30 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>				/* printf */
# include <stdlib.h>			/* malloc, free, exit, getenv */
# include <unistd.h>			/* access, chdir, close, dup, dup2, fork,
									getcwd,isatty, open, pipe, read, unlink,
									write, execve, ttyname, ttyslot, opendir,
									readdir, closedir */
# include <readline/readline.h>	/* readline, rl_clear_history, rl_on_new_line,
									rl_replace_line, rl_redisplay,
									add_history */
# include <sys/wait.h>			/* wait, waitpid, wait3, wait4 */
# include <signal.h>			/* signal, sigaction, sigemptyset, sigaddset,
									kill */
# include <sys/stat.h>			/* stat, lstat, fstat */
# include <termios.h>			/* tcsetattr, tcgetattr */
# include <errno.h>				/* perror, strerror */
# include <sys/ioctl.h>			/* ioctl */
# include <curses.h>			/* tgetent, tgetflag, tgetnum, tgetstr, tgoto,
									tputs */

# include "libft.h"
# include "get_next_line.h"

# define EXIT "exit"

typedef struct s_history
{
	int					id;
	char				*cmd;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;

typedef struct s_root
{
	t_history	*history;
}	t_root;

/* PROGRAM */
void		init_root(t_root *root);

/* PROMPT */
void		prompt(t_root *root, char **envp);
void		exit_prompt(char *cmd);

/* HISTORY */
t_history	*history_lstnew(int index, void *cmd);
void		history_clear(t_history **history);
void		history_add(t_history **history, char *cmd);
void		history_print(t_history *history);

#endif