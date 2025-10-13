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

static char	*clean_line(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	if (!line)
		return (NULL);
	return (line);
}

int	file_parsing(char *file, t_rt *rt)
{
	int		fd;
	char	*line;

	(void)rt;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Open file"));
	if (!check_filename(file))
		return (close(fd), print_error("Wrong scene format"));
	line = get_next_line(fd);
	if (!line)
		return (close(fd), print_error("Empty file"));
	// rt->sc = malloc(sizeof(t_scene));
	// if (!rt->sc)
	// 	return (close(fd), print_error("Malloc fail scene"));
	// rt->sc->amb.id = 0;
	// rt->sc->cam.id = 0;
	// rt->sc->light.id = 0;
	line = clean_line(line);
	if (!line)
		return (close(fd), print_error("Malloc fail ft_strtrim"))
	// line_parsing(fd, line, rt, 0);
	if (close(fd) == -1)
		return (print_error("Close file"));
	return (1);
}
