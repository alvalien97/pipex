/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:38:58 by hzsurf            #+#    #+#             */
/*   Updated: 2025/04/22 11:57:22 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *find_path (char *cmd, char **envp)
{
    char    **paths;
    char    *path;
    int     i;
    char    *part_path;

    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == 0)
        i++;
    paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin (paths[i], "/");
        path = ft_strjoin (part_path, cmd);
        free (part_path);
        if (access(path, F_OK) == 0)
            return (path);
        free (path);
        i++;
    }
    i = -1;
    while (paths[++i])
        free (paths[i]);
    free (paths);
    return (0);
}

void    error (void)
{
    perror ("Error");
    exit (EXIT_FAILURE);
}

void execute (char *argv, char **envp)
{
    char **cmd;
    int i;
    char *path;

    i = -1;
    cmd = ft_split (argv, ' ');
    path = find_path (cmd[0], envp);
    if (!path)
    {
        while (cmd[++i])
            free (cmd[i]);
        free (cmd);
        error();
    }
    if (execve (path, cmd, envp) == -1)
        error();
}
