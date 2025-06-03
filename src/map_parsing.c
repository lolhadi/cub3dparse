/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:16:18 by muhabin-          #+#    #+#             */
/*   Updated: 2025/06/03 15:11:58 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_check(t_data *data, char *line, int dir)
{
	if (dir == NORTH && !data->map_info.north)
		data->map_info.north = ft_strdup(line);
	else if (dir == SOUTH && !data->map_info.south)
		data->map_info.south = ft_strdup(line);
	else if (dir == WEST && !data->map_info.west)
		data->map_info.west = ft_strdup(line);
	else if (dir == EAST && !data->map_info.east)
		data->map_info.east = ft_strdup(line);
	else
		exit_error("Duplicating failed");
}
char	*get_path(char *line, int mode)
{
	char	*path;
	char	*trim;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		exit_error("Malloc failed");
	trim = ft_strtrim(path, " \n\t\r");
	free(path);
	if (!trim)
		exit_error("trimmed failed");
	if (mode == TEX)
	{
		if (ft_strlen(trim) < 4 || !ft_strnstr(trim + ft_strlen(trim) - 4, ".xpm", 4));
			exit_error("Invalid texture file");
	}
	return (trim);
}
void	parsing_map(t_data *data, char *line, int i)
{
	if (ft_strncmp(line + i, "NO", 2) == 0)
		texture_check(data, get_path(line + i, TEX), NORTH);
	else if (ft_strncmp(line + i, "SO", 2) == 0)
		texture_check(...);
	else if (ft_strncmp(line + i, "WE", 2) == 0)
		texture_check(...);
	else if (ft_strncmp(line + i, "EA", 2) == 0)
		texture_check(...);
	else if (ft_strncmp(line + i, "F", 1) == 0)
		color_check(...);
	else if (ft_strncmp(line + i, "C", 1) == 0)
		color_check(...);
	else if (line[i] == '1' || line[i] == '0')
		data->map_start = 1;
	else if (line[i] != '\0')
		exit_error(data, "Invalid params");
}
// WILL BE REFACTOR LATER SO CAN SEPARATE THE .cub TEXTURE AND MAP
int	readmap(t_data *data)
{
	int		i;
	char	*line;

	line = get_next_line(data->map_info.fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		parsing_map(data, line, i);
		if (data->map_start)
		{
			free(line);
			break;
		}
		free(line);
		line = get_next_line(data->map_info.fd);
	}
	return (0);
}
int	count_line(char *map)
{
	int		count;
	int		fd;
	char	*line;

	count = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (error_msg("failed to open", 2));
	else
	{
		line = get_next_line(fd);
		while (line)
		{
			count++;
			free(line);
			line = NULL;
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (count);
}
int	map_read(t_data *data, char *argv)
{
	t_map	maps;

	//TODO: using gnl to take the .cub so can do parsing map
	//count line of map so can malloc later
	maps.line_map = count_line(argv);
	//need to save the path name/file name may not needed
	// need to malloc so can create a space for the map to be copied
	maps.file = malloc(maps.line_map + 1 * sizeof(char *));
	if (!maps.file)
		return (error_msg("failed to malloc", 2));
	maps.fd = open(argv, O_RDONLY);
	if (maps.fd < 0)
		return (error_msg("failed to open",2));
	readmap(data);
	close(maps.fd);
	return (0);
}

/*
* utk map, kalau ada island tapi enclosed still consider okay,
	invalid kalau player pos bila flood fill tak enclosed map,
	boleh ada multiple island tapi player x boleh cross

*/

