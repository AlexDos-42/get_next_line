static char	*readline(const int fd, char *buff, int *ret)
{
	char	tmp[BUFF_SIZE + 1];
	char	*tmp2;
	
	*ret = read(fd, tmp, BUFF_SIZE);
	tmp[*ret] = '\0';
	tmp2 = buff;
	if (!(buff = ft_strjoin(buff, tmp)))
		return (NULL);
	ft_strdel(&tmp2);
	return (buff);
}

int			ft_cpy_end(char **line, char **buff)
{
	if (!(*line = ft_strdup(*buff)))
		return (-1);
	ft_bzero(*buff, ft_strlen(*buff));
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char		*buff = "";
	int				ret;
	char			*str;

	ret = 1;
	if (!line || fd < 0 || (buff[0] == '\0' && (!(buff = ft_strnew(0)))))
		return (-1);
	while (ret > 0)
	{
		if (!(buff = readline(fd, buff, &ret)))
			return (-1);
		if ((str = ft_strchr(buff, '\n')) != NULL)
		{
			printf("%s", "1\n");
			*str = '\0';
			if (!(*line = ft_strdup(buff)))
				return (-1);

			ft_memmove(buff, str + 1, ft_strlen(str + 1) + 1);
			printf("%s", "2\n");
			return (1);
		}
	}
	ft_strdel(&str);
	printf("%s", "free str");
	if (ret == 0 && ft_strlen(buff))
	{
		printf("%s", "ret == 0\n");
		ret = ft_cpy_end(&(*line), &buff);
	}
	return (ret);
}
