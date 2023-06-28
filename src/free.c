#include "minishell.h"

void    free_data(t_data	*data, int num_pipe)
{
	if (data->cmd)
		free(data->cmd);
	if (data->rdin_fd != 0)	
		ft_close(data->rdin_fd);
	if (data->rdout_fd != 0)
		ft_close(data->rdout_fd);

}