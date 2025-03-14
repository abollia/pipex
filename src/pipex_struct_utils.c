/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:41:51 by abollia           #+#    #+#             */
/*   Updated: 2025/03/10 11:10:46 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ppx_init(t_pipex *pipex)
{
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->open_error = 0;
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
	pipex->pid[0] = -1;
	pipex->pid[1] = -1;
	pipex->cmd_path = NULL;
	pipex->cmd_args = NULL;
}

void	ppx_close_all(t_pipex *pipex)
{
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	if (pipex->fd[1] != -1)
		close(pipex->fd[1]);
}

void	ppx_free_pipex(t_pipex *pipex)
{
	if (pipex->cmd_args)
		ft_ffa(pipex->cmd_args);
	free(pipex->cmd_path);
}
