#include "get_next_line.h"

static int			ft_exit(char **buffer, char **stock, int ret)
{
	if (ret >= 0 && (*buffer || *stock))
	{
		if (*buffer)
			free(*buffer);
		if (ret == 0 && *stock)
			free(*stock);
	}
	if (ret == -1)
	{
		if (*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
		if (*stock)
		{
			free(*stock);
			*stock = NULL;
		}
	}
	return (ret);
}

static char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;

	i = 0;
	if (!s)
		return (-1);
	if (start > (unsigned int)ft_strlen(s))
		return (-1);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (-1);
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
			return (-1);
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
	static char	*stock[1024];
	char		*tmp;

	if ((i = 0) || fd < 0 || fd > 1024 || BUFFER_SIZE < 1 || !line
			|| (!(buffer = ft_calloc((sizeof(char)), (BUFFER_SIZE + 1)))))
		return (ft_exit(&buffer, &stock[fd], -1));
	if (!stock[fd])
		if (!(stock[fd] = ft_calloc(0, 0)))
			return(ft_exit(&buffer, &stock[fd], -1));
	if ((ret = ft_read(fd, buffer, stock)) == -1)
		return (ft_exit(&buffer, &stock[fd], -1));
	while (stock[fd][i] && stock[fd][i] != '\n')
		i++;
	ret = ((stock)[fd][i] == '\n' ? 1 : 0);
	if (*line = ft_substr(stock[fd], 0, i) == -1)
		return (ft_exit(&buffer, &stock[fd], -1));
	if (!(tmp = ft_strdup(stock[fd][i] ? stock[fd] + i + 1 : stock[fd] + i)))
		return (ft_exit(&buffer, &stock[fd], -1));
	free(stock[fd]);
	stock[fd] = tmp;
	return (ft_exit(&buffer, &stock[fd], ret));
}
