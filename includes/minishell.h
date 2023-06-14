/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:28:46 by lchew             #+#    #+#             */
/*   Updated: 2023/06/14 19:31:08 by tzi-qi           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>

# define EXIT "exit"

# define PIPE "|"
# define RDIN "<"
# define HEREDOC "<<"
# define RDOUT ">"
# define RDAPP ">>"
# define SINGLE_QUOTE "\'"
# define DOUBLE_QUOTE "\""

typedef struct s_history
{
	int					id;
	char				*cmd;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;

typedef enum e_token
{
	COMMAND,
	PIPE_OP,
	RDIN_OP,
	RDOUT_OP,
	RDAPP_OP,
	HEREDOC_OP
}	t_token;

typedef struct s_lexer
{
	t_token			type;
	char			*value;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_tree
{
	t_token			token;
	char			*value;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_root
{
	t_history	*history;
	t_lexer		*lexer;
}	t_root;

/* PROGRAM */

void		init_root(t_root *root);
void		free_2D(char **str);

/* PROMPT */

void		prompt(t_root *root, char **envp);
void		exit_prompt(char *cmd);

/* HISTORY */

t_history	*history_node_new(int index, void *cmd);
void		history_clear(t_history **history);
void		history_add(t_history **history, char *cmd);
void		history_print(t_history *history);

/* PATH */

char		**find_path(void);
char		*the_legit_path(char *argv);

/* LEXER */

t_list		*lexer(char *cmd);
t_tree		*tree_node_new(t_token token, char *value, t_tree *left, t_tree *right);

/* PARSER */

t_tree		*parser(t_list *lexer, int num_tokens);
t_tree		*op_check(t_list *lexer, char *op, int num_tokens);
t_tree		*cmd_check(t_list *lexer, int num_tokens);
t_tree		*tree_node_new(t_token token, char *value, t_tree *left, t_tree *right);

void		print_tree(t_tree *root, int b);

void		exec_cmd(t_tree *node, char **envp);

/* FT_UTLIS */
int			ft_pipe(int p[2]);
int			ft_open(const char *file, int flags, int permission);
int			ft_fork(void);
int			ft_close(int fd);
int			ft_dup2(int new_fd, int old_fd);

/* PIPE */
void		children(t_tree *node, char **envp);

#endif
