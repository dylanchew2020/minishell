/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:28:46 by lchew             #+#    #+#             */
/*   Updated: 2023/07/20 20:08:54 by tzi-qi           ###   ########.fr       */
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

# define GREEN	"\033[1;32m"
# define BLUE	"\033[1;34m"
# define RESET	"\033[0m"

# define EXIT	"exit"

# define PIPE_OP	"|"
# define RDIN_OP	"<"
# define HEREDOC_OP	"<<"
# define RDOUT_OP	">"
# define RDAPP_OP	">>"

# define SINGLE_QUOTE	"\'"
# define DOUBLE_QUOTE	"\""

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
	int				stdin_tmp;
	int				stdout_tmp;
	t_list			*env_list;
	struct termios	previous;
	struct termios	current;
}	t_root;

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

/* PROGRAM */

void		init_root(t_root *root);
void		free_2d(char **str);

/* PROMPT */

void		prompt(t_root *sh, char **envp);
void		exit_prompt(char *cmd, t_root *sh);

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
int			count_token(char *cmd);
int			count_sp_char(char *cmd);
int			count_char(char *cmd);

/* PARSER */

t_tree		*parser(t_list *lexer, int num_tokens, t_root *sh);
t_tree		*token_check(t_list *lexer, char *op, int num_tokens, t_root *sh);
t_tree		*tree_node_new(t_token type, char *value, t_tree *left, \
							t_tree *right);
t_token		type_assign(char *value, t_root *sh);
void		init_token_check(t_token_check	*tkchk);
void		print_tree(t_tree *root, int b);
void		free_tree(t_tree *node);

/* EXECUTE */

void		recurse_bst(t_tree *node, char **envp, t_root *sh);
void		exec_cmd(char *argv, char **envp, t_root *sh);
void		redir_arg(t_tree *node, char **envp, t_root *sh);

/* FT_UTLIS */

int			ft_pipe(int p[2]);
int			ft_open(const char *file, int flags, int permission);
int			ft_fork(void);
int			ft_close(int fd);
int			ft_dup2(int new_fd, int old_fd);

/* FT_UTLIS2 */
void		ft_tcgetattr(int fd, struct termios *termios_p);
void		ft_tcsetattr(int fd, int optional_actions, \
						struct termios *termios_p);

/* PIPE */

void		children(t_tree *node, char **envp, t_root *sh);

/* REDIRECTION */

int			rdin_fd(char *node_value);
int			rdout_fd(char *node_value);
int			rdapp_fd(char *node_value);
int			heredoc_fd(char *node_value, t_root *sh);
char		*find_file(char *node_value);

/* ENV */
void		env_link_list(char **envp, t_list **env_list);
void		get_env(t_list **env_list);
char		*existed_env(char *key, t_list **env_list);
void		creat_new_env_node(char *key, char	*input, t_list **env_list);

/* BUILT IN */
int			builtin(char **cmd, t_list **env_list);

/* FREE */
void		del_data(void	*content);

/* EXPORT */

void		export(char **cmd, t_list **env_list);
char		*key_check(char *input);
char		*find_value(char *input);
void		add_link_list(char	*input, t_list	**env_list);
void		modified_value(t_env *data_node, char *input);

/* EXPAND */
char		*expand(char *cmd, t_list **env_list);

/* PWD */

void		pwd(void);

/* UNSET */

void		unset(t_list **env_list, char *key);

/* CD */
void		cd(char **value);
/* QUOTE */

int			is_quote(char c);
int			quote_count(char *cmd);
char		**cmd_quote_handler(char const *s, char c);

/*	SIGNAL */
void		signal_handler(int signum);
void		signals(t_root	*sh);
#endif
