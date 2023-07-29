/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse_bst_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:59:58 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/29 14:43:16 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recurse_rdin(t_tree *node, char **envp, t_root *sh)
{
	int	fd;

	fd = 0;
	fd = rdin_fd(node->value, sh);
	if (fd < 0)
		return ;
	ft_dup2(fd, STDIN_FILENO);
	ft_close(fd);
	redir_arg(node, envp, sh);
}

void	recurse_rdout(t_tree *node, char **envp, t_root *sh)
{
	int	fd;

	fd = 0;
	fd = rdout_fd(node->value, sh);
	if (fd < 0)
		return ;
	ft_dup2(fd, STDOUT_FILENO);
	ft_close(fd);
	redir_arg(node, envp, sh);
}

void	recurse_rdapp(t_tree *node, char **envp, t_root *sh)
{
	int	fd;

	fd = 0;
	fd = rdapp_fd(node->value, sh);
	if (fd < 0)
		return ;
	ft_dup2(fd, STDOUT_FILENO);
	ft_close(fd);
	redir_arg(node, envp, sh);
}

void	recurse_heredoc(t_tree *node, char **envp, t_root *sh)
{
	int	fd;

	fd = 0;
	ft_dup2(sh->stdin_tmp, STDIN_FILENO);
	fd = heredoc_fd(node->value, sh);
	if (fd < 0)
		return ;
	if (node->right == NULL || node->right->token != HEREDOC)
		ft_dup2(fd, STDIN_FILENO);
	ft_close(fd);
	redir_arg(node, envp, sh);
}
