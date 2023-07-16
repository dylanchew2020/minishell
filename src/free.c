/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:38:59 by tzi-qi            #+#    #+#             */
/*   Updated: 2023/07/05 17:39:20 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/**
 * del_data - Frees the memory associated with a t_env struct.
 *
 * @param content  Pointer to the t_env struct to be freed.
 */
void	del_data(void	*content)
{
	t_env	*data;

	data = (t_env *)content;
	free(data->key);
	free(data->value);
	free(data);
}
