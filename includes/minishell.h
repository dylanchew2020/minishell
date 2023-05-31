/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:28:46 by lchew             #+#    #+#             */
/*   Updated: 2023/05/31 16:28:06 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>

//prompt.c
void	prompt(char	**envp, char **argv);

//path.c
char	**find_path(char **envp);
void	complete_path(char **split);

#endif