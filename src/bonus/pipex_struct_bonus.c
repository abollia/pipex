/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:41:51 by abollia           #+#    #+#             */
/*   Updated: 2025/03/11 14:24:24 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	ppx_init(t_pipex *pipex, int cmd_count)
{
	int	i;

	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->open_error = 0;
	pipex->cmd_count = cmd_count;
	pipex->pipes = NULL;
	pipex->pid = NULL;
	pipex->cmd_path = NULL;
	pipex->cmd_args = NULL;
	pipex->flags = O_WRONLY | O_CREAT | O_TRUNC;
	pipex->pid = malloc(sizeof(pid_t) * cmd_count);
	if (!pipex->pid)
		ppx_exit_handler("Error - MALLOC", 0, pipex);
	pipex->pipes = malloc(sizeof(int *) * (cmd_count) - 1);
	if (!pipex->pipes)
		ppx_exit_handler("Error - MALLOC", 0, pipex);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipex->pipes[i]) == -1)
			ppx_exit_handler("Error - PIPE", 1, pipex);
		i++;
	}
}

void	ppx_close_all(t_pipex *pipex)
{
	int	i;

	close(pipex->outfile_fd);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}

void	ppx_free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->cmd_args)
		ft_ffa(pipex->cmd_args);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
	if (pipex->pipes)
	{
		i = 0;
		while (i < pipex->cmd_count - 1)
		{
			if (pipex->pipes[i])
				free(pipex->pipes[i]);
			i++;
		}
		free(pipex->pipes);
	}
	if (pipex->pid)
		free(pipex->pid);
}
