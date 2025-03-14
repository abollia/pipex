/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:26:43 by abollia           #+#    #+#             */
/*   Updated: 2025/03/11 14:46:41 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*ppx_find_cmd_path(char *cmd, char **env)
{
	char	*cmd_path;
	char	**paths;
	int		i;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (cmd);
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	paths = ft_split(*env + 5, ':');
	if (!paths)
		ppx_exit_handler("Error - MALLOC", 1);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin3(paths[i], "/", cmd);
		if (access(cmd_path, X_OK) == 0)
			return (ft_ffa(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	ft_ffa(paths);
	return (NULL);
}

static void	ppx_find_n_exec(char *cmd, t_pipex *pipex, char **env)
{
	pipex->cmd_args = ft_split(cmd, ' ');
	if (!pipex->cmd_args || !pipex->cmd_args[0])
	{
		ft_ffa(pipex->cmd_args);
		ppx_exit_handler("Error - Absent Command", 1);
	}
	pipex->cmd_path = ppx_find_cmd_path(pipex->cmd_args[0], env);
	if (!pipex->cmd_path || access(pipex->cmd_path, F_OK | X_OK) == -1)
	{
		if (!pipex->cmd_path)
			perror("Error - No path");
		else if (access(pipex->cmd_path, F_OK) == -1)
			perror("Error - Command found but no access");
		else
			perror("Error - Command found but cannot execute");
		ft_ffa(pipex->cmd_args);
		free(pipex->cmd_path);
		exit(127 - (pipex->cmd_path && access(pipex->cmd_path, F_OK) == 0));
	}
	execve(pipex->cmd_path, pipex->cmd_args, env);
	perror("execve");
	ft_ffa(pipex->cmd_args);
	free(pipex->cmd_path);
	exit(1);
}

static void	ppx_process(char *cmd, int cmd_id, t_pipex *pipex, char **env)
{
	if (pipex->pid[cmd_id] == -1)
		ppx_exit_handler("Error - FORK", 0);
	if (pipex->pid[cmd_id] == 0)
	{
		if (cmd_id == 0)
		{
			if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
				ppx_exit_handler("Error - DUP2", 0);
			if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
				ppx_exit_handler("Error - DUP2", 0);
		}
		else if (cmd_id == 1)
		{
			if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
				ppx_exit_handler("Error - DUP2", 0);
			if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
				ppx_exit_handler("Error - DUP2", 0);
		}
		ppx_close_all(pipex);
		ppx_find_n_exec(cmd, pipex, env);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		exit_code;

	if (!env || !*env)
		return (1);
	if (ac != 5)
		ppx_exit_handler("Error - Invalid number of arguments", 1);
	ppx_init(&pipex);
	ppx_open_file(av[1], 0, &pipex);
	ppx_open_file(av[4], 1, &pipex);
	if (pipe(pipex.fd) == -1)
		ppx_exit_handler("Error - PIPE", 1);
	pipex.pid[0] = fork();
	ppx_process(av[2], 0, &pipex, env);
	pipex.pid[1] = fork();
	ppx_process(av[3], 1, &pipex, env);
	ppx_close_all(&pipex);
	exit_code = ppx_wait_n_exit(&pipex, 2);
	ppx_free_pipex(&pipex);
	return (exit_code);
}
