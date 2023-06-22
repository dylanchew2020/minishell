/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:18 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/06/22 21:23:56 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_link	*lstnew(char *content)
{
	t_link	*list;

	list = ft_calloc(1, sizeof(t_link));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

t_link	*lstlast(t_link *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_link **lst, t_link *new)
{
	t_link	*temp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		temp = lstlast(temp);
		temp->next = new;
	}
}

void	prompt(t_root *root, char **envp)
{
	char	*cmd;
	char	**path;
	t_list	*cmd_lexer;
	t_list	*iter;
	t_link	*head;
	t_link	*body;
	t_link	*tmp;
	pid_t	child;
	int		status;
	int		i;

	path = find_path();
	while (1)
	{
		cmd = readline("\033[1;32mminishell$\033[0m ");
		exit_prompt(cmd);
		history_add(&root->history, cmd);
		if (!ft_strncmp(cmd, "history", 8))
			history_print(root->history);
		cmd_lexer = lexer(cmd);
		iter = cmd_lexer;
		head = NULL;
		while (iter)
		{
			body = lstnew((char *)iter->content);
			lstadd_back(&head, body);
			iter = iter->next;
		}
		tmp = head;
		while (tmp)
		{
			printf("lexer : |%s|\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		i = pipe_num(head);
		printf("%i\n", i);
		// if (i >= 1)
		// 	pipe_exec(cmd_lexer, envp, i);
		// else
		// 	execution((char *)cmd_lexer->content, envp);
		// ft_lstclear(&cmd_lexer, free);
		free(cmd);
	}
	history_clear(&root->history);
	return ;
}

void	exit_prompt(char *cmd)
{
	if (!cmd || !ft_strncmp(cmd, EXIT, 5))
	{
		free(cmd);
		clear_history();
		exit(0);
	}
}

void	print_tree(t_tree *root, int b)
{
	static int level;

	if (b == 0)
		++level;
	if (root == NULL)
	{
		printf("NULL\n");
		if (b == 0)
			--level;
		return ;
	}
	printf("%u : %s\n", root->token, root->value);
	printf("left %i  ", level);
	print_tree(root->left, 0);
	printf("right %i  ", level);
	print_tree(root->right, 0);
	--level;
}