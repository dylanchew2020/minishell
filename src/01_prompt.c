/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchew <lchew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/08/02 17:57:30 by lchew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt_str(void);
static int	lexer_paser_exec(t_root *sh, char **envp, char **cmd);

/**
 * @brief Main prompt loop of the shell.
 *
 * This function controls the main prompt loop of the shell, managing signals,
 * reading user input, and invoking lexer, parser, and execution functions.
 *
 * @param sh The shell root structure.
 * @param envp Environment variables.
 */
void	prompt(t_root *sh, char **envp)
{
	char	*cmd;
	char	*prompt_str;

	while (TRUE)
	{
		signals(1);
		prompt_str = get_prompt_str();
		cmd = readline(prompt_str);
		free(prompt_str);
		if (!cmd)
			break ;
		if (*cmd)
		{
			if (lexer_paser_exec(sh, envp, &cmd) == -1)
				continue ;
		}
		free(cmd);
		if (sh->exit_cmd_flag == 1)
			break ;
	}
}

/**
 * @brief Generates the prompt string with current working directory.
 *
 * This function constructs the prompt string to be displayed, replacing the
 * home directory with tilde and adding color codes for aesthetic purposes.
 *
 * @return The formatted prompt string.
 */
static char	*get_prompt_str(void)
{
	char	cwd[1024];
	char	*p;
	size_t	p_size;

	ft_memset(cwd, 0, 1024);
	getcwd(cwd, 1024);
	if (ft_strncmp(cwd, getenv("HOME"), ft_strlen(getenv("HOME"))) == 0)
	{
		cwd[0] = '~';
		ft_memmove(cwd + 1, cwd + ft_strlen(getenv("HOME")), \
				ft_strlen(cwd + ft_strlen(getenv("HOME"))) + 1);
	}
	p_size = ft_strlen(cwd) + ft_strlen(GREEN) + ft_strlen(BLUE) \
			+ ft_strlen(RESET) + 13 + 8;
	p = (char *)ft_calloc(p_size, sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, "\001" GREEN "\002", p_size);
	ft_strlcat(p, "Minishell:", p_size);
	ft_strlcat(p, "\001" BLUE "\002", p_size);
	ft_strlcat(p, cwd, p_size);
	ft_strlcat(p, "\001" RESET "\002", p_size);
	ft_strlcat(p, "$ ", p_size);
	return (p);
}

/**
 * @brief Executes the lexer, parser, and recursive execution for the given
 * command.
 *
 * This function takes the user's command input, processes it through the
 * lexer and parser, then recursively executes the command, handling shell
 * attributes and signals as necessary.
 *
 * @param sh The shell root structure.
 * @param envp Environment variables.
 * @param cmd Command string input by the user.
 * @return 0 if successful, -1 if an error occurred.
 */
static int	lexer_paser_exec(t_root *sh, char **envp, char **cmd)
{
	char	*tmp;
	t_list	*cmd_lexer;
	t_tree	*head;

	history_add(&sh->history, *cmd);
	tmp = *cmd;
	*cmd = expand(*cmd, &sh->env_list);
	free(tmp);
	cmd_lexer = lexer(*cmd);
	if (cmd_lexer == NULL)
		return (-1);
	head = parser(cmd_lexer, ft_lstsize(cmd_lexer), sh);
	ft_tcsetattr(STDIN_FILENO, TCSANOW, &sh->previous);
	signals(0);
	recurse_bst(head, envp, sh);
	reset_data(sh, &cmd_lexer, &head);
	return (0);
}
