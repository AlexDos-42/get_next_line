#include "get_next_line.h"

static int	get_line(int const fd, char *buff, char *s[fd])
{
	int		ret;
	char	*tmp;

	while (!(ft_strchr(buff, '\n')) &&
			(ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = s[fd];
		s[fd] = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
	}
	ft_strdel(&buff);
	if (ret == -1)
		return (-1);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char		*s[10240];
	char			*buff;
	int				ret;
	char			*str;
	char			*tmp;

	buff = ft_strnew(BUFF_SIZE);
	if (fd < 0 || !line || !buff || fd > 10240)
		return (-1);
	if (!s[fd])
		s[fd] = ft_strnew(1);
	if ((ret = get_line(fd, buff, s)) == -1)
		return (-1);
	if ((str = ft_strchr(s[fd], '\n')))
	{
		*line = ft_strsub(s[fd], 0, str - s[fd]);
		tmp = s[fd];
		s[fd] = ft_strdup(str + 1);
		ft_strdel(&tmp);
		return (1);
	}
	*line = ft_strdup(s[fd]);
	s[fd] = NULL;
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
