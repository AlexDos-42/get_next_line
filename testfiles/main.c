/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:36:29 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/19 18:19:57 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

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

static void			ft_bzero(void *str, size_t n)
{
	char	*tab;

	tab = str;
	while (n)
		tab[--n] = '\0';
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
		return (-1);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!stock[fd])
		stock[fd] = ft_calloc(0, 0);
	if ((ret = ft_read(fd, buffer, stock)) == -1)
		   return (-1);	
	while (stock[fd][i] && stock[fd][i] != '\n')
		i++;
	ret = ((stock)[fd][i] == '\n' ? 1 : 0);
	if (!(*line = ft_substr(stock[fd], 0, i)))
		return (-1);
	if (!(tmp = ft_strdup(stock[fd][i] ? stock[fd] + i + 1 : stock[fd] + i)))
		return (-1);
	free(stock[fd]);
	stock[fd] = tmp;
	return (ret);
}
/*
   int          main(int ac, char **av)
   {
   int          fd;
   int          ret;
   int          i;
   char *line;

   if (ac != 2)
   return (0);
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
   }*/
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
/*
   int main(int argc, char **argv)
   {
   int fd;
   int ret;
   int line;
   char *buff;


   line = 0;
   if (argc == 1)
   fd = 0;
   else
   fd = open((argv[1]), O_RDONLY);
   while ((ret = get_next_line(fd, &buff)) > 0)
   {
   printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
   free(buff);
   }
   if (ret == -1)
   printf("-----------\nError\n");
   else if (ret == 0)
   printf("-----------\nEnd of file\n");
   close(fd);
   return (0);
   }*/
