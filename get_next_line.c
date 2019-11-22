/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:54:08 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/19 18:23:14 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			ft_exit(char *buffer, char *stock)
{
	if (buffer)
		free(buffer);
	if (stock)
		free(stock);
	return (-1);
}

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

int					ft_read(int fd, char *buffer, char *stock[fd])
{
	int		ret;
	char	*tmp;

	while (!ft_strchr(buffer, '\n') && (ret = read(fd, buffer, BUFFER_SIZE)))
	{
		if (ret == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[ret] = '\0';
		if (!(tmp = ft_strjoin(stock[fd], buffer)))
			return (-1);
		stock[fd] = tmp;
	}
	free(buffer);
	return (ret);
}

int					get_next_line(int fd, char **line)
{
	char		*buffer;
	int			ret;
	int			i;
	static char	*stock[10240];
	char		*tmp;

	if ((i = 0) || fd < 0 || fd > 10240 || BUFFER_SIZE <= 0 || !line
		|| !(buffer = (char *)malloc(sizeof(char ) * (BUFFER_SIZE + 1))))
		return (ft_exit);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!stock[fd])
		stock[fd] = ft_calloc(0, 0);
	if ((ret = ft_read(fd, buffer, stock)) == -1)
		return (ft_exit);
	while (stock[fd][i] && stock[fd][i] != '\n')
		i++;
	ret = ((stock)[fd][i] == '\n' ? 1 : 0);
	if (!(*line = ft_substr(stock[fd], 0, i)))
		return (ft_exit);
	if (!(tmp = ft_strdup(stock[fd][i] ? stock[fd] + i + 1 : stock[fd] + i)))
		return (ft_exit);
	free(stock[fd]);
	stock[fd] = tmp;
	return (ret);
}
