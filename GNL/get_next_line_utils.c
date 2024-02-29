/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:47 by mhotting          #+#    #+#             */
/*   Updated: 2023/11/28 16:59:17 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	char			*res;
	unsigned char	c_char;

	res = (char *) s;
	c_char = (unsigned char) c;
	while (*res != '\0')
	{
		if (*res == c_char)
			return (res);
		res++;
	}
	if (*res == c_char)
		return (res);
	return (NULL);
}

/*
 *	Appends s2 at the end of s1.
 *	Only len_s2 chars of s2 are appended (len_s2 = max(len_s2, ft_strlen(s2)))
 *	A new string is allocated and old s1 is freed.
 *	In case of error, nothing happens and 0 is returned.
 *	On success 1 is returned.
 */
int	gnl_join(char **s1, char *s2, size_t len_s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_temp;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	if (len_s2 == 0)
		return (1);
	len_temp = ft_strlen(s2);
	if (len_s2 > len_temp)
		len_s2 = len_temp;
	len_s1 = ft_strlen(*s1);
	res = (char *) malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (res == NULL)
		return (0);
	i = -1;
	while (++i < len_s1)
		res[i] = (*s1)[i];
	while (i < len_s1 + len_s2)
		res[i++] = *(s2++);
	res[i] = '\0';
	free(*s1);
	*s1 = res;
	return (1);
}

/*
 *	Cleans memory for all given pointer.
 *	If a pointer is NULL, free is not called (adds flexibility to the function).
 *	If store is provided, all the store list and its content are freed.
 */
void	*gnl_clean_memory(t_list **store, char *buffer, char *res)
{
	t_list			*next;
	t_buffer_save	*buffer_save;

	if (buffer != NULL)
		free(buffer);
	if (res != NULL)
		free(res);
	if (store != NULL && *store != NULL)
	{
		while (*store != NULL)
		{
			next = (*store)->next;
			buffer_save = (t_buffer_save *)((*store)->content);
			if (buffer_save != NULL)
			{
				free(buffer_save->buffer);
				free(buffer_save);
			}
			free(*store);
			*store = next;
		}
	}
	return (NULL);
}
