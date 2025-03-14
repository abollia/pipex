/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:53:09 by abollia           #+#    #+#             */
/*   Updated: 2025/03/11 14:30:08 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	ppx_heredoc(t_pipex *pipex, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ppx_exit_handler("Error - HERE_DOC", 1, pipex);
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
				&& line[ft_strlen(limiter)] == '\n'))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	pipex->infile_fd = open(".here_doc_tmp", O_RDONLY);
	if (pipex->infile_fd < 0)
		ppx_exit_handler("Error - INFILE", 1, pipex);
}

void	ppx_open_file(char *file_name, int file_id, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->flags = O_WRONLY | O_CREAT | O_APPEND;
	if (file_id == 0)
	{
		pipex->infile_fd = open(file_name, O_RDONLY);
		if (pipex->infile_fd == -1)
			ft_dprintf(2, "Error infile opening failed\n");
	}
	else if (file_id == 1)
	{
		pipex->outfile_fd = open(file_name, pipex->flags, 0644);
		if (pipex->outfile_fd == -1)
			ft_dprintf(2, "Error outfile opening failed\n");
	}
}

void	ppx_exit_handler(char *message, int errcode, t_pipex *pipex)
{
	if (errcode == 0)
		perror(message);
	else if (errcode == 1)
		ft_dprintf(2, "%s\n", message);
	ppx_free_pipex(pipex);
	exit(EXIT_FAILURE);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, s3);
	if (!res)
		return (NULL);
	free(temp);
	return (res);
}

int	ppx_wait_n_exit(t_pipex *pipex)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	if (pipex->open_error)
		exit_code = 1;
	return (exit_code);
}
