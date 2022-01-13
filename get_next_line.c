/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelisabe <kelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 18:05:16 by kelisabe          #+#    #+#             */
/*   Updated: 2022/01/13 21:47:00 by kelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	clear_old_buf(char **s1, char *s2, int is_reverse, int is_copy_buf)
{
	char	*orig_buf;

	if (is_copy_buf != 0)
	{
		free(*s1);
		*s1 = 0;
		return ;
	}
	orig_buf = *s1;
	if (is_reverse == 0)
		*s1 = ft_strjoin(*s1, s2);
	else
		*s1 = ft_strjoin(s2, *s1);
	free(orig_buf);
}

static int	slash_n_in_copy_buf(char **copy_buf, char **buf)
{
	char	*slash_n;

	slash_n = 0;
	if (*copy_buf != NULL)
		slash_n = ft_strchr(*copy_buf, '\n');
	if (slash_n != NULL)
	{
		*slash_n = '\0';
		*buf = ft_strdup(*copy_buf);
		if (*(slash_n + 1) != '\0')
		{
			free(*copy_buf);
			*copy_buf = ft_strdup(slash_n + 1);
		}
		else
			clear_old_buf(copy_buf, "", 0, 1);
		clear_old_buf(buf, "\n", 0, 0);
		return (1);
	}
	return (0);
}

static int	replace_slash_n(char **copy_buf, char **buf)
{
	char	*slash_n;

	if (*copy_buf != NULL)
	{
		clear_old_buf(buf, *copy_buf, 1, 0);
		clear_old_buf(copy_buf, "", 0, 1);
	}
	slash_n = ft_strchr(*buf, '\n');
	if (slash_n != NULL)
	{
		*slash_n = '\0';
		if (*(slash_n + 1) != '\0')
			*copy_buf = ft_strdup(slash_n + 1);
		clear_old_buf(buf, "\n", 0, 0);
		return (1);
	}
	*copy_buf = ft_strdup(*buf);
	free(*buf);
	return (0);
}

static int	read_buf(int fd, char **buf, int *count_bytes, char **copy_buf)
{
	*buf = malloc(sizeof(char ) * (BUFFER_SIZE + 1));
	if (*buf == NULL)
		return (-1);
	(*buf)[0] = '\0';
	*count_bytes = read(fd, *buf, BUFFER_SIZE);
	if ((*buf)[0] == '\0')
	{
		free(*buf);
		if (*copy_buf != NULL)
		{
			*buf = ft_strdup(*copy_buf);
			clear_old_buf(copy_buf, "", 0, 1);
			return (1);
		}
		return (-1);
	}
	(*buf)[*count_bytes] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			count_bytes;
	static char	*copy_buf;
	int			read_res;

	if (fd == -1)
		return (0);
	count_bytes = 1;
	if (slash_n_in_copy_buf(&copy_buf, &buf) == 1)
		return (buf);
	while (count_bytes > 0)
	{
		read_res = read_buf(fd, &buf, &count_bytes, &copy_buf);
		if (read_res == 1)
			return (buf);
		else if (read_res == -1)
			return (0);
		if (replace_slash_n(&copy_buf, &buf) == 1)
			return (buf);
	}
	return (0);
}
