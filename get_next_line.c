/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelisabe <kelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 18:05:16 by kelisabe          #+#    #+#             */
/*   Updated: 2022/01/08 22:02:56 by kelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if (c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (str == 0)
		return (0);
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (0);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	return (s3);
}

char *get_next_line(int fd)
{
	char *buf;
	int count_bytes;
	char *slash_n;
	static char *copy_buf;
	char *orig_buf;

	count_bytes = 1;
	while (count_bytes > 0)
	{
		buf = malloc(sizeof(char )*(BUFFER_SIZE + 1));
		count_bytes = read(fd, buf, BUFFER_SIZE);
		buf[count_bytes] = '\0';
		slash_n = ft_strchr(buf, '\n');
		if (slash_n != NULL)
		{
			*slash_n = '\0';
			copy_buf = ft_strdup(slash_n + 1);
			orig_buf = buf;
			buf = ft_strjoin(buf, "\n");
			free(orig_buf);
			return (buf);
		}
	}
	return (buf);
}

int	main()
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	return (0);
}
