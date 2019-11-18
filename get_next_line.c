/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:54:08 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/18 19:10:16 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;
	size_t		size_len;

	i = 0;
	if (!s)
		return (0);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	size_len = ft_strlen(s);
	if (start < size_len)
	{
		while (i < len)
		{
			str[i] = s[start];
			i++;
			start++;
		}
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count == 0 || size == 0)
	{
		size = 1;
		count = 1;
	}
	if (!(str = malloc(size * count)))
		return (NULL);
	if (size!= 0)
	{
		while (size--)
			((unsigned char *)str)[size] = '\0';
	}
	return (str);
}

void	ft_bzero(void *str, size_t n)
{
	char *tab;

	tab = str;
	while (n)
	{
		tab[--n] = '\0';
	}
}

int             get_next_line(int fd, char **line)
{
    char            *buffer;
    int             ret;
    int             i;
    static char     *stock;
	char			*tmp;

    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || !line || !(buffer = (char *)malloc(sizeof(char ) * (BUFFER_SIZE + 1))))
        return (-1);
	ft_bzero(buffer, BUFFER_SIZE + 1); 
    if (!stock)
        stock = ft_calloc(0,0);
    while (!ft_strchr(buffer, '\n') && (ret = read(fd, buffer, BUFFER_SIZE)))
    {
        buffer[ret] = '\0';
        tmp = ft_strjoin(stock, buffer);
		free(*stock);
		stock = tmp;
    }
	printf("ret  %d\n", ret);
	free(buffer);
    i = 0;
	while (stock[i] && stock[i] != '\n')
        i++;
    *line = ft_substr(stock, 0, i);
    stock = ft_strdup(stock + i + 1);
	return (ret > 0 ? 1 : 0);
}
/*
int			main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int i = 0 ;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%d  %s\n", i++, line);
		free(line);
	}
	return (0);
}
*/
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
    //printf("%d\n", s);
    close(fd);
    free(line);
    return (0);
}
/*
int        main(int argc, char **argv)
{
    int        fd;
    char    *line;
    int        i;
    int ret;
    if (argc != 2)
        return (0);
    i = 0;
    (void)argc;
    //fd = 0;
    fd = open((argv[1]), O_RDONLY);
    while ((ret = get_next_line(fd, &line)))
    {
        printf("\n\n = = = = = > GNL : line = |%s|\n", line);
        printf(" = = = = = > GNL : ret = %d\n\n\n", ret);
        free(line);
    }
    if (ret == 0)
    {
        printf("\n\n = = = = = > GNL : line = |%s|\n", line);
        printf(" = = = = = > GNL : ret = %d\n\n\n", ret);
        free(line);
    }
    system("leaks a.out");
    return (0);
}*/
