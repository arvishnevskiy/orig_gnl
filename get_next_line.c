/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelisabe <kelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 18:05:16 by kelisabe          #+#    #+#             */
/*   Updated: 2022/01/12 23:47:57 by kelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

// char	*put_slash_n(char *slash_n, char *buf)
// {
// 	static char *orig_buf;
// 	static char *copy_buf;

// 	slash_n = NULL;
// 	if(slash_n != NULL)
// 	{
// 		*slash_n = '\0';
// 		orig_buf = copy_buf;
// 		buf = ft_strdup(copy_buf);
// 		copy_buf = ft_strdup(slash_n + 1);
// 		orig_buf = buf;
// 		buf = ft_strjoin(buf, "\n");
// 		free(orig_buf);
// 		return (buf);
// 	}
// 	return (0);
// }

char	*get_next_line(int fd)
{
	char *buf;
	int count_bytes;
	char *slash_n;
	static char *copy_buf;
	char *orig_buf;

	if (fd == -1)
		return (0);
	count_bytes = 1;
	slash_n = NULL;
	if (copy_buf != NULL)
		slash_n = ft_strchr(copy_buf, '\n');
	if (slash_n != NULL)
	{
		*slash_n = '\0';
		orig_buf = copy_buf;
		buf = ft_strdup(copy_buf);
		// free(orig_buf);
		if (buf == NULL)
			return (0);
		if (*(slash_n + 1) != '\0')
		{
			free(copy_buf);
			copy_buf = ft_strdup(slash_n + 1);
			if (copy_buf == NULL)
				return (0);
		}
		else
		{
			free(copy_buf);
			copy_buf = 0;
		}
		orig_buf = buf;
		buf = ft_strjoin(buf, "\n");
		free(orig_buf);
		// free(copy_buf);
		return (buf);
	}
	while (count_bytes > 0)
	{
		buf = malloc(sizeof(char )*(BUFFER_SIZE + 1));
		if (buf == NULL)
			return (0);
		buf[0] = '\0';
		count_bytes = read(fd, buf, BUFFER_SIZE);
		if (*buf == '\0')
		{
			free(buf);
			if (copy_buf != NULL)
			{
				buf = ft_strdup(copy_buf);
				free(copy_buf);
				copy_buf = 0;
				return (buf);
			}
			return (0);
		}
		buf[count_bytes] = '\0';
		if (copy_buf != NULL)
		{
			orig_buf = buf;
			buf = ft_strjoin(copy_buf, buf);
			free(copy_buf);
			copy_buf = NULL;
			free(orig_buf);
		}
		slash_n = ft_strchr(buf, '\n');
		if (slash_n != NULL)
		{
			*slash_n = '\0';
			if (*(slash_n + 1) != '\0')
				copy_buf = ft_strdup(slash_n + 1);
			orig_buf = buf;
			buf = ft_strjoin(buf, "\n");
			free(orig_buf);
			return (buf);
		}
		copy_buf = ft_strdup(buf);
		free(buf);
	}
	return (0);
}

// int	main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("text.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)) != 0){
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }