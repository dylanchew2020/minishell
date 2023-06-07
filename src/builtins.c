#include "minishell.h"

int builtins_check(char *cmd)
{
    if (ft_strnstr(cmd, "echo", 4) != 0)
        return (1);
    else if (ft_strnstr(cmd, "cd", 2) != 0)
        return (1);
    else if (ft_strnstr(cmd, "pwd", 3) != 0)
        return (1);
    else if (ft_strnstr(cmd, "export", 6) != 0)
        return (1);
    else if (ft_strnstr(cmd, "unset", 5) != 0)
        return (1);
    else if (ft_strnstr(cmd, "env", 3) != 0)
        return (1);
    else if (ft_strnstr(cmd, "exit", 4) != 0)
        return (1);
    else
        return (0);
}