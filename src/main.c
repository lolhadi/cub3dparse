/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:47:07 by muhabin-          #+#    #+#             */
/*   Updated: 2025/07/11 16:59:16 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(const char *msg)
{
	printf("Error\n%s\n",msg);
	exit(EXIT_FAILURE);
}
void	init_data(t_data *data)
{
	data->map_start = 0;
	data->map_info.ceiling = -1;
	data->map_info.floor = -1;
}
int main(int argc, char **argv)
{
	t_data	data;
	// void *mlx;
	// void *mlx_win;

  /* LUL parts to do */
  //TODO: check for argument
	if (argc < 2)
		return (error_msg("Error\nWrong argument", 1));
  //TODO: .cub file format parsing
	if (!is_cub_file(argv[1]))
		return (error_msg("Error\nNeed to be .cub file", 1)); //can be error
	//TODO: Map parsing
	init_data(&data); //can use ft_bzero to initiliaze data
	if (map_read(&data, argv[1]) != 0)
		return (1);

	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world");
	// mlx_loop(mlx);
}
