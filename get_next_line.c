/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:38 by mhotting          #+#    #+#             */
/*   Updated: 2023/11/28 17:00:43 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 *	Retrieves a buffer from the given store, searching for the given fd.
 *	If a buffer is found, it removes the corresponding node
 *	and returns the buffer.
 *	Returns NULL if no buffer was found.
 */
static char	*store_get_buffer(t_list **store, int fd)
{
	t_list	*prev;
	t_list	*current;
	char	*buffer;

	if (store == NULL || *store == NULL)
		return (NULL);
	prev = NULL;
	current = *store;
	while (current != NULL)
	{
		if (((t_buffer_save *)current->content)->fd == fd)
		{
			if (prev == NULL)
				*store = current->next;
			else
				prev->next = current->next;
			buffer = ((t_buffer_save *)current->content)->buffer;
			free(current->content);
			free(current);
			return (buffer);
		}
		prev = current;
		current = current->next;
	}
	return (NULL);
}

/*
 *	Saves a buffer into the store by creating a new node of type t_buffer_save.
 *	The new buffer is added at the beginning of the store.
 */
static int	store_save(t_list **store, char *buffer, int fd)
{
	t_list			*node;
	t_buffer_save	*save;

	if (store == NULL || buffer == NULL)
		return (0);
	if (buffer[0] == '\0')
	{
		free(buffer);
		return (1);
	}
	save = (t_buffer_save *) malloc(sizeof(t_buffer_save));
	if (save == NULL)
		return (0);
	save->fd = fd;
	save->buffer = buffer;
	node = (t_list *) malloc(sizeof(t_list));
	if (node == NULL)
	{
		free(save);
		return (0);
	}
	node->content = (void *) save;
	node->next = *store;
	*store = node;
	return (1);
}

/*
 *	Extracts the content of buffer in order to append it to res.
 *	If a new line is found into buffer:
 *		- the end of the previous line is appended to res;
 *		- buffer will contain the beginning of the new line;
 * 		- nl_found is set to 1;
 * 	Else:
 * 		- the whole buffer is appended to res;
 * 		- buffer is cleaned;
 */
static int	buffer_get(char *buffer, char **res, int *nl_found)
{
	char	*nl_buffer;
	size_t	buffer_len;

	nl_buffer = ft_strchr(buffer, '\n');
	if (nl_buffer == NULL)
		buffer_len = ft_strlen(buffer);
	else
	{
		nl_buffer++;
		*nl_found = 1;
		buffer_len = nl_buffer - buffer;
	}
	if (!gnl_join(res, buffer, buffer_len))
		return (0);
	if (nl_buffer != NULL)
	{
		while (*nl_buffer)
			*(buffer++) = *(nl_buffer++);
	}
	while (*buffer != '\0')
		*(buffer++) = '\0';
	return (1);
}

/*
 *	Returns a buffer by getting its previous value from the store
 *	or by creating a new one.
 *	If a previous state of buffer is found, the first line is extracted from it
 *	and put into res, buffer is then the remaining part from extraction or empty.
 *	If a new line is encountered during the extraction, nl_found is set to 1.
 */
static char	*buffer_init(t_list **store, int fd, char **res, int *nl_found)
{
	char	*buffer;
	size_t	i;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	buffer = store_get_buffer(store, fd);
	if (buffer == NULL)
	{
		buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		i = 0;
		if (buffer != NULL)
			while (i < BUFFER_SIZE + 1)
				buffer[i++] = '\0';
		return (buffer);
	}
	if (!buffer_get(buffer, res, nl_found))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

/*
 *	Reads into fd until next line break or until EOF.
 *	Can be called multiple times in order to get all the lines of a file.
 *	Different fd can be passed without affecting the function behaviour
 */
char	*get_next_line(int fd)
{
	static t_list	*store = NULL;
	char			*buffer;
	ssize_t			nb_read;
	char			*res;
	int				nl_found;

	res = NULL;
	nb_read = 1;
	nl_found = 0;
	buffer = buffer_init(&store, fd, &res, &nl_found);
	if (fd == -1 || buffer == NULL)
		return (gnl_clean_memory(&store, buffer, res));
	while (nb_read != 0 && !nl_found)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
			return (gnl_clean_memory(NULL, buffer, res));
		if (!buffer_get(buffer, &res, &nl_found))
			return (gnl_clean_memory(&store, buffer, res));
	}
	if (!store_save(&store, buffer, fd))
		return (gnl_clean_memory(&store, buffer, res));
	return (res);
}
