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

t_data	*data_init(t_link *head, int i);

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
	t_list	*cmd_lexer;
	t_list	*iter;
	t_link	*head;
	t_link	*body;
	t_link	*tmp;
	t_tree	*left;
	t_token	type;
	t_tree	*right;
	t_data	*data;
	int		i;

	pid_t	child;
	int	status;

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
			type = type_assign(body->content, left, right, root);
			if (type != PIPE && type != RDIN && type != RDOUT && type != HEREDOC)
				type = COMMAND;
			body->token = type;
			iter = iter->next;
		}
		tmp = head;
		while (tmp)
		{
			printf("lexer : |%s| && |%i|\n", (char *)tmp->content, tmp->token);
			tmp = tmp->next;
		}
		i = pipe_num(head);
		printf("%i\n", i);
		data = data_init(head, i);
		if (i >= 1)
			pipe_exec(data, envp, i);
		else
		{
			printf("it enter here\n");
			child = ft_fork();
			if (child == 0)
			{
				if (data[0].rdin_fd != 0)
					dup2(data[0].rdin_fd, 0);
				if (data[0].rdout_fd != 0)
					dup2(data[0].rdout_fd, 1);
				execution(data[0].cmd, envp);
			}
			waitpid(child, &status, 0);
		}
		free_data(data, i);
		free(data);
		ft_lstclear(&cmd_lexer, free);
		free(cmd);
	}
	history_clear(&root->history);
	return ;
}

t_data	*data_init(t_link *head, int i)
{
	t_data	*data;
	t_link	*tmp;
	int		j;

	data = (t_data	*)ft_calloc(i + 1, sizeof(t_data));
	j = 0;
	tmp = head;
	while (tmp != NULL)
	{
		while (tmp != NULL && tmp->token != PIPE)
		{
			printf("tmp : |%s| && |%i|\n", tmp->content, tmp->token);
			if (tmp->token == RDIN)
			{
				printf("rdint\n");
				data[j].rdin_fd = rdin_fd(tmp->content);
			}
			else if (tmp->token == RDOUT)
			{
				printf("rdout\n");
				data[j].rdout_fd = rdout_fd(tmp->content);
			}
			else if (tmp->token == COMMAND)
			{
				printf("command\n");
				data[j].cmd = ft_strdup(tmp->content);
				printf("data : |%s|\n", data[j].cmd);
			}
			tmp = tmp->next;
		}
		if (tmp != NULL)
			tmp = tmp->next;
		printf("data : |%s| && rdint |%i| && rdout |%i|\n", data[j].cmd, data[j].rdin_fd, data[j].rdout_fd);
		j++;
	}
	return (data);
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