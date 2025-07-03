/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:16:18 by muhabin-          #+#    #+#             */
/*   Updated: 2025/07/03 14:47:19 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	flood_fill(t_data *data, char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[x] || y >= (int)ft_strlen(map[x]))
}
void	count_check(int count)
{
	if (count == 0)
		exit_error("Error: No player detected");
	if (count > 1)
		exit_error("Error: Multiple Player");
}
//TODO: need to change to original map

void	find_player(t_data *data, char **copy_map)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (copy_map[++i])
	{
		j = 0;
		while (copy_map[i][j])
		{
			if (copy_map[i][j] == 'N' || copy_map[i][j] == 'S'
				|| copy_map[i][j] == 'E' || copy_map[i][j] == 'W')
			{
				data->player.player_x = i;
				data->player.player_y = j;
				data->player.p_direction = copy_map[i][j];
				copy_map[i][j] = '0';
				count++;
				flood_fill(data, copy_map, i , j);
			}
			j++;
		}
	}
	count_check(count);
}

void	valid_char(t_data *data, char **map_copy)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			c = map_copy[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ')
				exit_error("Error Invalid Characters");
			j++;
		}
		i++;
	}
}
void	main_parse(t_data *data, char **map_copy)
{
	int	i;
	int	j;
	int	only_space;

	i = 0;
	while (map_copy[i])
	{
		j = 0;
		only_space = 1; // assume that the line is all space first
		while (map_copy[i][j])
		{
			if (map_copy[i][j] != ' ' && map_copy[i][j] != '\t' && map_copy[i][j] != '\n')
			{
				only_space = 0; //found a character means the whole line tak semua space
				break;
			}
			j++;
		}
		if (only_space)
				exit_error("invalid map");
		i++;
	}
}
char	**copy_map(char **map)
{
	char	**copy;
	int		lines;
	int		i;

	i = 0;
	while (map[lines])
		lines++;
	copy = ft_calloc(lines + 1, sizeof(char *));
	if (!copy)
		exit_error("failed to malloc");
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			exit_error("bro failed to make copy map");
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
/*
 * NEED TO CHANGE
 *	: JUST USED THE ORIGINAL MAP FOR MAIN PARSE,
 *	: THEN USED THE ORIGINAL MAP TO VALID CHAR ALSO
 *	: USED ORIGINAL MAP FOR FINDING THE PLAYER
 *	: FILL THE MAP WITH (0) UNTIL THE MAXIMUM COLUMN, IT BE WELL FORMATED
 *	: THEN COPY THE MAP
 *	: FLOOD FILL USING COPY MAP
*/
void	parse_map(t_data *data)
{
	int		i;
	char	*line;
	char 	**map_copy;

	i = 0;
	data->map_info.file = ft_calloc(data->map_info.line_cub + 1,
			sizeof(char *));
	if (!data->map_info.file)
		exit_error("failed to malloc");
	line = get_next_line(data->map_info.fd);
	while(line)
	{
		data->map_info.file[i] = ft_strdup(line);
		if (!data->map_info.file[i])
			exit_error("failed malloc map");
		i++;
		free(line);
		line = get_next_line(data->map_info.fd);
	}
	data->map_info.file[i] = NULL;
	map_copy = copy_map(data->map_info.file);
	main_parse(data, map_copy);
	valid_char(data, map_copy);
	find_player(data, map_copy);
}

int	everything_good(t_data *data)
{
	if (!data->map_info.east || !data->map_info.south || !data->map_info.west
		|| !data->map_info.north || data->map_info.floor == -1
		|| data->map_info.ceiling == -1)
		return (1);
	return (0);
}
//can be in the utils
void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void	save_color(t_data * data,char **rgb, int mode)
{
	int	r;
	int	g;
	int	b;
	unsigned int	color;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	color = (r << 16 | g << 8 | b);
	if (mode == FLOOR && data->map_info.floor == -1)
		data->map_info.floor = color;
	else if (mode == CEILING && data->map_info.ceiling == -1)
		data->map_info.ceiling = color;
	else
		exit_error("duping color failed");
}
int	valid_color(char **rgb)
{
	int	i;
	int	j;
	int	value;

	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	i = 0;
	while(i < 3)
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (0);
			j++;
		}
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			return (0);
		i++;
	}
	return (1);
}
void	color_check(t_data *data, char *line, int mode)
{
	int		i;
	int		j;
	char	*trim;
	char	**rgb;

	i = 0;
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	trim = ft_strdup(line + i);
	if (!trim)
		error_exit("failed to copy");
	rgb = ft_split(trim, ',');
	if (!valid_color(rgb))
		exit_error("wrong color");
	save_color(data, rgb, mode);
	free(trim);
	free_array(rgb);
}

void	can_open_file(t_data *data, char *file, int fd)
{
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("File cannot be open");
	close(fd);
}

void	texture_check(t_data *data, char *line, int dir)
{
	//need to add check if the texture file can be open
	can_open_file(data, line, 0);
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
void	parsing_config(t_data *data, char *line, int i)
{
	if (ft_strncmp(line + i, "NO", 2) == 0)
		texture_check(data, get_path(line + i, TEX), NORTH);
	else if (ft_strncmp(line + i, "SO", 2) == 0)
		texture_check(data, get_path(line + i, TEX), SOUTH);
	else if (ft_strncmp(line + i, "WE", 2) == 0)
		texture_check(data, get_path(line + i, TEX), WEST);
	else if (ft_strncmp(line + i, "EA", 2) == 0)
		texture_check(data, get_path(line + i, TEX), EAST);
	else if (ft_strncmp(line + i, "F", 1) == 0)
		color_check(data, line + i, FLOOR);
	else if (ft_strncmp(line + i, "C", 1) == 0)
		color_check(data, line + i, CEILING);
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
		parsing_config(data, line, i);
		if (data->map_start)
		{
			free(line);
			break;
		}
		free(line);
		line = get_next_line(data->map_info.fd);
	}
	if (everything_good(data))
		exit_error("Wrong Configuration");
	parse_map(data);
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
	//TODO: using gnl to take the .cub so can do parsing map
	//count line of map so can malloc later
	data->map_info.line_cub = count_line(argv);
	//need to save the path name/file name may not needed
	// need to malloc so can create a space for the map to be copied
	data->map_info.fd = open(argv, O_RDONLY);
	if (data->map_info.fd < 0)
		return (error_msg("failed to open",2));
	readmap(data);
	close(data->map_info.fd);
	return (0);
}

/*
* utk map, kalau ada island tapi enclosed still consider okay,
	invalid kalau player pos bila flood fill tak enclosed map,
	boleh ada multiple island tapi player x boleh cross

*/
