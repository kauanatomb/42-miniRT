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
	char	*trimmed;

	i = -1;
	while (line && line[++i])
		if (line[i] == '\t' || line[i] == '\n')
			line[i] = ' ';
	trimmed = ft_strtrim(line, " ");
	free(line);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}

static int	parse_element(char *line, t_rt *rt)
{
	if (ft_strncmp("A ", line, 2) == 0)
		return (ambiance_parsing(line, rt));
	if (ft_strncmp("C ", line, 2) == 0)
		return (camera_parsing(line, rt));
	if (ft_strncmp("L ", line, 2) == 0)
		return (light_parsing(line, rt));
	if (ft_strncmp("sp ", line, 3) == 0)
		return (sphere_parsing(line, rt));
	if (ft_strncmp("pl ", line, 3) == 0)
		return (plane_parsing(line, rt));
	if (ft_strncmp("cy ", line, 3) == 0)
		return (cy_parsing(line, rt));
	if (line[0] == '#' || line[0] == '\0')
		return (1);
	return (print_error("Unknown element in scene"));
}

int	line_parsing(int fd, char *line, t_rt *rt)
{
	int	ret;

	while (line)
	{
		ret = parse_element(line, rt);
		free(line);
		if (!ret)
			return (get_next_line(-2), 0);
		line = get_next_line(fd);
		if (line)
			line = clean_line(line);
	}
	return (free(line), 1);
}

int	file_parsing(char *file, t_rt *rt)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Open file"));
	if (!check_filename(file))
		return (close(fd), print_error("Wrong scene format"));
	line = get_next_line(fd);
	if (!line)
		return (close(fd), print_error("Empty file"));
	rt->sc = ft_calloc(sizeof(t_scene), 1);
	if (!rt->sc)
		return (close(fd), print_error("Malloc fail scene"));
	line = clean_line(line);
	if (!line)
		return (close(fd), print_error("Malloc fail ft_strtrim"));
	if (!line_parsing(fd, line, rt))
		return (close(fd), 0);
	if (close(fd) == -1)
		return (print_error("Close file"));
	if (!rt->sc->has_cam || !rt->sc->has_amb)
		return (print_error("No camera or ambience light"));
	return (1);
}
