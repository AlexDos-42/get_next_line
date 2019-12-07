/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:54:08 by alesanto          #+#    #+#             */
/*   Updated: 2019/12/07 13:10:03 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;

	i = 0;
	if (!s)
		return (0);
	if (start > (unsigned int)ft_strlen(s))
		return (NULL);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void			*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count == 0 || size == 0)
	{
		size = 1;
		count = 1;
	}
	if (!(str = malloc(size * count)))
		return (NULL);
	if (size != 0)
	{
		while (size--)
			((unsigned char *)str)[size] = '\0';
	}
	return (str);
}

int					ft_read(int fd, char *buffer, char **stock)
{
	int		ret;

	while (!ft_strchr(stock[fd], '\n') && (ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		stock[fd] = ft_strjoin(stock[fd], buffer);
	}
	return (ret);
}

int					get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	int			ret;
	int			i;
	static char	*stock[1024];
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!stock[fd])
		stock[fd] = ft_calloc(0, 0);
	if ((ret = ft_read(fd, buffer, stock)) == -1)
		return (-1);
	i = 0;
	while (stock[fd][i] && stock[fd][i] != '\n')
		i++;
	*line = ft_substr(stock[fd], 0, i);
	tmp = stock[fd][i] ? ft_strdup(stock[fd] + i + 1) : NULL;
	free(stock[fd]);
	stock[fd] = tmp;
	if (ret != 0 || stock[fd])
		return (1);
	return (0);
}
