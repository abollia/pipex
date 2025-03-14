/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:26:43 by abollia           #+#    #+#             */
/*   Updated: 2025/03/11 14:46:13 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

static char	*ppx_find_cmd_path(char *cmd, char **env, t_pipex *pipex)
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
		ppx_exit_handler("Error - MALLOC", 1, pipex);
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
		ppx_exit_handler("Error - Absent Command", 1, pipex);
	pipex->cmd_path = ppx_find_cmd_path(pipex->cmd_args[0], env, pipex);
	if (!pipex->cmd_path || access(pipex->cmd_path, F_OK | X_OK) == -1)
	{
		if (!pipex->cmd_path)
			ft_dprintf(2, "Error - No path");
		else if (access(pipex->cmd_path, F_OK) == -1)
			perror("Error - Found");
		else
			perror("Error - Execute");
		ppx_free_pipex(pipex);
		exit(127 - (pipex->cmd_path && access(pipex->cmd_path, F_OK) == 0));
	}
	execve(pipex->cmd_path, pipex->cmd_args, env);
	perror("execve");
	ppx_free_pipex(pipex);
	exit(1);
}

static void	ppx_process(char *cmd, int cmd_id, t_pipex *pipex, char **env)
{
	if (pipex->pid[cmd_id] == -1)
		ppx_exit_handler("Error - FORK", 0, pipex);
	if (pipex->pid[cmd_id] == 0)
	{
		if (cmd_id == 0)
		{
			if (dup2(pipex->infile_fd, STDIN_FILENO) == -1
				|| dup2(pipex->pipes[cmd_id][1], STDOUT_FILENO) == -1)
				ppx_exit_handler("Error - DUP2", 0, pipex);
		}
		else if (cmd_id == pipex->cmd_count - 1)
		{
			if (dup2(pipex->pipes[cmd_id - 1][0], STDIN_FILENO) == -1
				|| dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
				ppx_exit_handler("Error - DUP2", 0, pipex);
		}
		else
		{
			if (dup2(pipex->pipes[cmd_id - 1][0], STDIN_FILENO) == -1
				|| dup2(pipex->pipes[cmd_id][1], STDOUT_FILENO) == -1)
				ppx_exit_handler("Error - DUP2", 0, pipex);
		}
		ppx_close_all(pipex);
		ppx_find_n_exec(cmd, pipex, env);
	}
}

static void	ppx_prime(int ac, char *arg1, t_pipex *pipex)
{
	if (ac < 5)
	{
		ft_dprintf(2, "Error - Not enough arguments");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(arg1, "here_doc", 9) == 0)
	{
		pipex->here_doc = 1;
		pipex->cmd_start = 3;
	}
	else
	{
		pipex->here_doc = 0;
		pipex->cmd_start = 2;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		i;
	int		exit_code;

	if (!env || !*env)
		return (1);
	ppx_prime(ac, av[1], &pipex);
	ppx_init(&pipex, ac - pipex.cmd_start - 1);
	if (pipex.here_doc)
		ppx_heredoc(&pipex, av[2]);
	else
		ppx_open_file(av[1], 0, &pipex);
	ppx_open_file(av[ac - 1], 1, &pipex);
	i = 0;
	while (i < pipex.cmd_count)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] == 0)
			ppx_process(av[i + pipex.cmd_start], i, &pipex, env);
		i++;
	}
	ppx_close_all(&pipex);
	exit_code = ppx_wait_n_exit(&pipex);
	ppx_free_pipex(&pipex);
	return (exit_code);
}
