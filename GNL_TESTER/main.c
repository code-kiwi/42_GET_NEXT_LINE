/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:05:07 by mhotting          #+#    #+#             */
/*   Updated: 2023/11/25 10:17:34 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	int		count;
	char	*read_line;
	char	*read_line2;

	read_line = NULL;
	read_line2 = NULL;

	// Reading from STDIN
	if (argc == 1)
	{
		fd = 0;
		count = 0;
		read_line = get_next_line(fd);
		while (read_line != NULL)
		{
			printf("LINE %3d: %s", count, read_line);
			count++;
			free(read_line);
			read_line = get_next_line(fd);
		}
		return (0);
	}

	// Reading from one or two files
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR - Could not open given file\n");
		return (-1);
	}
	count = 0;

	// One file
	if (argc == 2)
	{
		do
		{
			read_line = get_next_line(fd);
			if (read_line == NULL)
				break ;
			printf("LINE %3d: %s", count, read_line);
			count++;
			free(read_line);
		} while (read_line != NULL);
		close(fd);
		return (0);
	}

	// Two files (atlernates between both files)
	fd2 = open(argv[2], O_RDONLY);
	if (fd2 == -1)
	{
		printf("ERROR - Could not open given file\n");
		return (-1);
	}
	count = 0;
	do
	{
		read_line = get_next_line(fd);
		read_line2 = get_next_line(fd2);
		if (read_line == NULL && read_line2 == NULL)
			break ;
		printf("FILE 1: (LINE %3d) %s", count, read_line);
		if (read_line == NULL || strchr(read_line, '\n') == NULL)
			printf("\n");
		printf("\033[0;36m");
		printf("FILE 2: (LINE %3d) %s", count, read_line2);
		if (read_line2 == NULL || strchr(read_line2, '\n') == NULL)
			printf("\n");
		printf("\033[0m");
		count++;
		free(read_line);
		free(read_line2);
	} while (1);
	return (0);
}
