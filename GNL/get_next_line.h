/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:57 by mhotting          #+#    #+#             */
/*   Updated: 2023/11/28 17:01:23 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_buffer_save
{
	int		fd;
	char	*buffer;
}	t_buffer_save;

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		gnl_join(char **s1, char *s2, size_t s2_len);
void	*gnl_clean_memory(t_list **store, char *buffer, char *res);
char	*get_next_line(int fd);

#endif
