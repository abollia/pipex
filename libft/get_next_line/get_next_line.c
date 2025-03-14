/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:38:48 by abollia           #+#    #+#             */
/*   Updated: 2025/02/11 09:37:39 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*extract_line(char *stash)
{
	char	*res;
	size_t	len;

	if (!*stash)
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	res = ft_substr(stash, 0, len);
	if (!res)
		return (NULL);
	stash = NULL;
	return (res);
}

static char	*join_lines(char *line1, char *line2)
{
	char	*res;

	if (!line1)
		line1 = ft_strdup("");
	res = ft_strjoin(line1, line2);
	free(line1);
	free(line2);
	return (res);
}

static void	update_stash(char *stash)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	j = 0;
	while (stash[i])
		stash[j++] = stash[i++];
	stash[j] = '\0';
}

static char	*get_next_line2(char *stash, char *line, int fd)
{
	int		readreturn;

	readreturn = 1;
	while (readreturn != 0)
	{
		if (!stash[0])
		{
			readreturn = read(fd, stash, BUFFER_SIZE);
			if (readreturn <= 0)
			{
				if (readreturn == 0)
					break ;
				return (free(line), NULL);
			}
			stash[readreturn] = '\0';
		}
		line = join_lines(line, extract_line(stash));
		if (ft_strchr(stash, '\n'))
		{
			update_stash(stash);
			break ;
		}
		stash[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[512][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 512)
		return (NULL);
	line = NULL;
	line = get_next_line2(stash[fd], line, fd);
	return (line);
}
