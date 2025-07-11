/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:14:14 by ayeap             #+#    #+#             */
/*   Updated: 2025/07/11 11:37:42 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../minilibx-linux/mlx.h"
# include "../library/inc/libft.h"

# include <stdio.h> // open, close, read, printf, perror
# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // write
# include <fcntl.h> // open
# include <string.h> // strerror

//Configure
# define NORTH		1
# define SOUTH		2
# define WEST		3
# define EAST		4
# define FLOOR		5
# define CEILING	6

//Type configure
# define TEX		1
# define COL		2

//Files type
# define CUB		1
# define XPM		2

typedef struct s_map
{
	int				fd; //fd for opening the map
	int				line_cub; // how many lines inside the map files
	int				floor;
	int				ceiling;
	char			**file;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				empty_line;

}	t_map;

typedef struct s_player
{
	int				player_x;
	int				player_y;
	char			p_direction;
}	t_player;

typedef struct s_data
{
	char		**maps; // an 2d array of map
	int			map_start;
	t_map		map_info;
	t_player	player;

}	t_data;

// utils.c
int		error_msg(char *msg, int status);
int		is_cub_file(char *argv);
void	exit_error(const char *msg);
int		empty_line(char *line);
int		is_map_line(char *line);

int	map_read(t_data *data, char *argv);
#endif
