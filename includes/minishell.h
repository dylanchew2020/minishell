/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:28:46 by lchew             #+#    #+#             */
/*   Updated: 2023/06/28 19:32:25 by lchew            ###   ########.fr       */
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

# define PIPE_OP "|"
# define RDIN_OP "<"
# define HEREDOC_OP "<<"
# define RDOUT_OP ">"
# define RDAPP_OP ">>"
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
	END,
	RDAPP,
	HEREDOC,
	RDIN,
	RDOUT,
	PIPE,
	COMMAND,
	NO_OF_TOKEN_TYPES
}	t_token;

typedef struct s_token_check
{
	char	*op;
	t_token	token;
}	t_token_check;

typedef struct s_tree
{
	t_token			token;
	char			*value;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_root
{
	t_history		*history;
	t_token_check	tkchk[NO_OF_TOKEN_TYPES];
}	t_root;

typedef struct s_pipe
{
	int	p[2];
	int	previous_fd;
}	t_pipe;

/* PROGRAM */

void		init_root(t_root *root);
void		free_2d(char **str);

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

t_tree		*parser(t_list *lexer, int num_tokens, t_root *sh);
t_tree		*token_check(t_list *lexer, char *op, int num_tokens, t_root *sh);
t_tree		*tree_node_new(t_token type, char *value, t_tree *left, t_tree *right);
t_token		type_assign(char	*value, t_tree *left, t_tree *right, t_root *sh);
void		init_token_check(t_token_check	*tkchk);
void		print_tree(t_tree *root, int b);

/* EXECUTE */

void		recurse_bst(t_tree *node, char **envp);
void		exec_cmd(char *argv, char **envp);
void		redir_arg(t_tree *node, char **envp);

/* FT_UTLIS */

int			ft_pipe(int p[2]);
int			ft_open(const char *file, int flags, int permission);
int			ft_fork(void);
int			ft_close(int fd);
int			ft_dup2(int new_fd, int old_fd);

/* PIPE */

void		children(t_tree *node, char **envp);

/* REDIRECTION */

int			rdin_fd(char *node_value);
int			rdout_fd(char *node_value);
char		*find_file(char *node_value);

#endif
