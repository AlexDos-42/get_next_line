/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:54:08 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/13 17:57:57 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void				*ft_free_tabtab(char **s)
{
	if (s == NULL)
		return (NULL);
	if (*s != NULL)
	{
		free(*s);
		*s = NULL;
	}
	return (s);
}

void				*ft_memmove(void *dst, const void *src, size_t n)
{
	if (src < dst && src + n > dst)
	{
		while (n > 0)
		{
			n--;
			((char*)dst)[n] = ((char*)src)[n];
		}
		return (dst + n);
	}
	return (ft_memcpy(dst, src, n));
}

char				*ft_buffer(const int fd, char *val, int *ret)
{
	char			buf[BUFFER_SIZE + 1];
	char			*tmp;

	*ret = read(fd, buf, BUFFER_SIZE);
	if (buf[*ret - 1] != '\n' && *ret < BUFFER_SIZE && *ret > 0)
	{
		buf[*ret] = '\n';
		buf[*ret + 1] = '\0';
	}
	else
		buf[*ret] = '\0';
	tmp = val;
	val = ft_strjoin(val, buf);
	ft_free_tabtab(&tmp);
	return (val);
}

int					get_next_line(int fd, char **line)
{
	char *str;
	static char *val;
	int ret;
	char			buf[2];

	str = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!val)
		val = ft_strdup("");
	ret = 1;
	while (ret > 0)
	{
		if ((str = ft_strchr(val, '\n')) != NULL)
		{
			*str++ = '\0';
			*line = ft_strdup(val);
			if (!line)
				return (-1);
			ft_memmove(val, str, ft_strlen(str) + 1);
			if (!read(fd, buf, 2))
				return (0);
			return (1);
		}
		val = ft_buffer(fd, val, &ret);
	}
	if (ret == 0)
		*line = ft_strdup(val - 1);
	return (ret);
}

int  main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     s;
    char    *str;
    line = NULL;
    line = malloc(sizeof(char));
    (void)argc;
    fd = (open(argv[1], O_RDONLY));
    //s = ft_find_line(fd, str);
    while ((s = get_next_line(fd, &line)) != 0)
    {
        printf("%d %s\n||||||||||||||||||||||||||||||||\n", s, line);
    }
    printf("%d %s\n||||||||||||||||||||||||||||||||\n", s, line);
    //printf("%d\n", s);
    close(fd);
    free(line);
    return (0);
}
