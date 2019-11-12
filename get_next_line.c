/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:54:08 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/12 17:59:53 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void		*ft_free_tabtab(char **s)
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

void	*ft_memmove(void *dst, const void *src, size_t n)
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

static char			*ft_buffer(const int fd, char *val, int *ret)
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

int	get_next_line(int fd, char **line)
{
	char *str;
	static char *val;
	int ret;

	str = 0;
	if (fd < 0 || !line)
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
			return (1);
		}
		val = ft_buffer(fd, val, &ret);
//		printf("val ||||| %s\n", val);
	}
	if (ret == 0)
		*line = ft_strdup(val);
	return (ret);
}

/* int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	int		i;
	char	*line;

	fd = open(av[1], O_RDONLY);
	line = NULL;
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("final : ret %d -> line  [%s]\n ||||||||||||||||||||||||||| \n\n", ret, line);
		i++;
	}
	close(fd);
	free(line);
	return (0);
}
*/
