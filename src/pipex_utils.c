/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:53:09 by abollia           #+#    #+#             */
/*   Updated: 2025/03/10 13:12:59 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ppx_open_file(char *file_name, int file_id, t_pipex *pipex)
{
	if (file_id == 0)
	{
		pipex->infile_fd = open(file_name, O_RDONLY);
		if (pipex->infile_fd == -1)
			ft_dprintf(2, "Error infile opening failed\n");
	}
	else if (file_id == 1)
	{
		pipex->outfile_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile_fd == -1)
			ft_dprintf(2, "Error outfile opening failed\n");
	}
}

void	ppx_exit_handler(char *message, int errcode)
{
	if (errcode == 0)
		perror(message);
	else if (errcode == 1)
		ft_dprintf(2, "%s\n", message);
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

int	ppx_wait_n_exit(t_pipex *pipex, int child_count)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < child_count)
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
