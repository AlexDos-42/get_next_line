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
   }

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
}

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
   }
