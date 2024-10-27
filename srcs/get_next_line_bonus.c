/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:58:18 by tuaydin           #+#    #+#             */
/*   Updated: 2024/10/27 23:00:00 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_del_line(char *buffer)
{
	char	*rtn;
	int		i;

	i = 0;
	rtn = NULL;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	i++;
	rtn = ft_substr(buffer, i, ft_strlen(buffer) - i);
	free(buffer);
	return (rtn);
}

char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	return (line);
}

char	*ft_fill_buff(char *buffer, int fd)
{
	char	*temp;
	int		rd;

	rd = BUFFER_SIZE;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (ft_strchr(buffer, '\n') == 0 && rd == BUFFER_SIZE)
	{
		rd = read(fd, temp, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buffer);
			free(temp);
			return (NULL);
		}
		temp[rd] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	free(temp);
	if (!buffer[0])
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*ft_read_file(int fd, char *buffer)
{
	int		rd;
	char	*rtn;

	rtn = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!rtn)
		return (NULL);
	rd = read(fd, rtn, BUFFER_SIZE);
	if (rd == -1)
	{
		free(rtn);
		free(buffer);
		return (NULL);
	}
	rtn[rd] = '\0';
	return (rtn);
}

char	*get_next_line(int fd)
{
	static char	*buffer[10024];
	char		*line;

	if (fd < 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = ft_fill_buff(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = ft_get_line(buffer[fd]);
	buffer[fd] = ft_del_line(buffer[fd]);
	return (line);
}