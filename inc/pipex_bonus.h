/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:07 by abollia           #+#    #+#             */
/*   Updated: 2025/03/11 13:55:39 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		cmd_count;
	int		here_doc;
	int		cmd_start;
	int		flags;
	int		**pipes;
	pid_t	*pid;
	char	*cmd_path;
	char	**cmd_args;
}	t_pipex;

/* ************************************************************************** */
/*---------------------------\\\\\___BONUS___/////----------------------------*/
void	ppx_free_pipex(t_pipex *pipex);
void	ppx_close_all(t_pipex *pipex);
void	ppx_init(t_pipex *pipex, int cmd_count);
void	ppx_exit_handler(char *message, int errcode, t_pipex *pipex);
void	ppx_open_file(char *file_name, int file_id, t_pipex *pipex);
int		ppx_wait_n_exit(t_pipex *pipex);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	ppx_heredoc(t_pipex *pipex, char *limiter);

/* ************************************************************************** */
#endif