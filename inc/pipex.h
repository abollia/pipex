/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:07 by abollia           #+#    #+#             */
/*   Updated: 2025/03/10 13:23:23 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		open_error;
	int		fd[2];
	pid_t	pid[2];
	char	*cmd_path;
	char	**cmd_args;
}	t_pipex;

/* ************************************************************************** */
/*-------------------------\\\\\___MANDATORY___/////--------------------------*/
void	ppx_free_pipex(t_pipex *pipex);
void	ppx_close_all(t_pipex *pipex);
void	ppx_init(t_pipex *pipex);
void	ppx_exit_handler(char *message, int errcode);
void	ppx_open_file(char *file_name, int file_id, t_pipex *pipex);
int		ppx_wait_n_exit(t_pipex *pipex, int child_count);
char	*ft_strjoin3(char *s1, char *s2, char *s3);

/* ************************************************************************** */
#endif