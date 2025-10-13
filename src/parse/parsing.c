/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (!(file[len - 2] == '.' && file[len - 1] == 'r' && file[len] == 't'))
		return (0);
	return (1);
}

int	file_parsing(char *file, t_rt *rt)
{
	int		fd;
	char	*line;

	(void)rt;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("File error"));
	if (!check_filename(file))
		return (close(fd), print_error("Wrong scene format"));
	line = get_next_line(fd);
	if (!line)
		return (close(fd), print_error("Empty file"));
	if (close(fd) == -1)
		return (print_error("Error close file"));
	return (0);
}