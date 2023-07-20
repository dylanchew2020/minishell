/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/20 19:53:04 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*get_prompt_str(void);

void	prompt(t_root *sh, char **envp)
{
	char	*cmd;
	char	*tmp;
	t_list	*cmd_lexer;
	t_list	*tmp_lexer;
	t_tree	*head;
	char	*prompt_str;

	env_link_list(envp, &sh->env_list);
	while (1)
	{
		signals(sh);
		prompt_str = get_prompt_str();
		cmd = readline(prompt_str);
		if (!cmd)
			exit_prompt(cmd, sh);
		if (*cmd)
		{
			history_add(&sh->history, cmd);
			tmp = cmd;
			cmd = expand(cmd, &sh->env_list);
			free(tmp);
			exit_prompt(cmd, sh);
			cmd_lexer = lexer(cmd);
			if (cmd_lexer == NULL)
				continue ;
			head = parser(cmd_lexer, ft_lstsize(cmd_lexer), sh);
			print_tree(head, 0);
			recurse_bst(head, envp, sh);
			ft_dup2(sh->stdin_tmp, STDIN_FILENO);
			ft_dup2(sh->stdout_tmp, STDOUT_FILENO);
			if (access(".here_doc_tmp", F_OK & X_OK) == 0)
				unlink(".here_doc_tmp");
			free_tree(head);
			while (cmd_lexer)
			{
				tmp_lexer = cmd_lexer->next;
				free(cmd_lexer);
				cmd_lexer = tmp_lexer;
			}
		}
		free(prompt_str);
		free(cmd);
	}
	history_clear(&sh->history);
	ft_lstclear(&sh->env_list, del_data);
	return ;
}

static char	*get_prompt_str(void)
{
	char	cwd[1024];
	char	*p;
	size_t	p_size;

	getcwd(cwd, 1024);
	p_size = ft_strlen(cwd) + ft_strlen(GREEN) + ft_strlen(BLUE)\
			+ ft_strlen(RESET) + 13;
	p = (char *)ft_calloc(p_size, sizeof(char));
	if (p == NULL)
	{
		free(cwd);
		return (NULL);
	}
	ft_strlcpy(p, GREEN, p_size);
	ft_strlcat(p, "Minishell:", p_size);
	ft_strlcat(p, BLUE, p_size);
	ft_strlcat(p, cwd, p_size);
	ft_strlcat(p, RESET, p_size);
	ft_strlcat(p, "$ ", p_size);
	return (p);
}

void	exit_prompt(char *cmd, t_root *sh)
{
	int	i;
	if (!cmd || !ft_strncmp(cmd, EXIT, 5))
	{
		free(cmd);
		clear_history();
		ft_close(sh->stdin_tmp);
		ft_close(sh->stdout_tmp);
		i = open("Makefile", O_RDONLY);
		printf("i = %i\n", i);
		close(i);
		ft_lstclear(&sh->env_list, del_data);
		exit(0);
	}
}

void	print_tree(t_tree *root, int b)
{
	static int	level;

	if (b == 0)
		++level;
	if (root == NULL)
	{
		printf("NULL\n");
		if (b == 0)
			--level;
		return ;
	}
	printf("token (%u): (%s)\n", root->token, root->value);
	printf("left %i  ", level);
	print_tree(root->left, 0);
	printf("right %i  ", level);
	print_tree(root->right, 0);
	--level;
}

void	free_tree(t_tree *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	free(node->value);
	free(node);
}
