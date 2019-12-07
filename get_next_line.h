/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:10:28 by alesanto          #+#    #+#             */
/*   Updated: 2019/12/07 12:52:23 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int			ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
int			get_next_line(int fd, char **line);
char		*ft_strdup(const char *src);
char		*ft_strchr(const char *s, int c);

#endif
