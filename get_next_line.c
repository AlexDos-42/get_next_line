#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2, int size)
{
	int		i;
	int		j;
	char	*str;
	int len_s1;	

	i = 0;
	j = 0;
	len_s1 = 0;
	while (s1)
		len_s1++;
	if (!(str = malloc(sizeof(char) * (len_s1 + size + 1))))
		return (NULL);
	while (s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && j < size)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	check(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	get_next_line(int fd, char **line)
{
	char buf[BUFFER_SIZE];
	int ret;
	char *tmp;
	int			i; 
	static int val;

	tmp = 0;
	ret = 1;
	i = BUFFER_SIZE;
	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1)
		return (-1);
	printf("%s\n", *line);
	while ((i == BUFFER_SIZE || buf[i] != '\n') && ret > 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[ret] = '\0';
			i = check(buf);
			if ((tmp = ft_strjoin(*line, buf, i)))
			{
				if (*line)
					free(*line);
				*line = tmp;
			}
			else
				ret = -2;
		}
	}
	val = check() + 1;
	return (ret);
}

int		main(int ac, char **av)
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
		printf("%d -> [%s]\n", i, line);
		i++;
	}
	close(fd);
	return (0);
}
