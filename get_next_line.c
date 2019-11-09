#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char buf[BUFFER_SIZE];
	int ret;

	while (ret = read(fd, buf, BUFF_SIZE))
		{
		
		}
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
		free(line);
		i++;
	}
	free(line);
	close(fd);
	return (0);
}
