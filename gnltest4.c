int	get_next_line(const int fd, char **line)
{
	static char	*str[OPEN_MAX];
	int			i;
	int			ret;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;

	if ((i = 0) || fd < 0 || fd > OPEN_MAX || !line || BUFF_SIZE < 0
		|| read(fd, buf, 0) || !(str[fd] = str[fd] ? str[fd] : ft_strnew(0)))
		return (-1);
	while ((!ft_strchr(str[fd], '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[ret] = '\0';
		if (!(tmp = ft_strjoin(str[fd], buf)))
			return (-1);
		free(str[fd]);
		str[fd] = tmp;
	}
	while (str[fd][i] && str[fd][i] != '\n')
		i++;
	*line = str[fd];
	if (!(str[fd] = ft_strdup(str[fd][i] ? str[fd] + i + 1 : str[fd] + i)))
		return (-1);
	ret = (*line)[i] == '\n' ? 1 : 0;
	(*line)[i] = '\0';
	return (ret || i);
}
