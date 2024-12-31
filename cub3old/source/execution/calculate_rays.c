/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:37:28 by disilva           #+#    #+#             */
/*   Updated: 2024/12/31 01:48:45 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	draw_image(t_data *data);
void	ray_vector(int window_column, t_data *data);
void	x_step_size(t_data *data);
void	y_step_size(t_data *data);
void	dda(t_data *data);
void	wall_distance(t_data *data);

void	calculate_camera_plane_length(t_data *data)
{
	double	fov_rand;

	fov_rand = FOV * (M_PI / 180);
	data->ray_info.camera_plane_length = 2 * sin(FOV / 2 * (M_PI / 180));
}

void	run_game(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_LENGTH, "cub3D", true);
	ft_mlx_error(*data);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_LENGTH);
	ft_img_error(*data);
	mlx_key_hook(data->mlx, esc_hook, data);
	mlx_loop_hook(data->mlx, check_movement, data);
	calculate_camera_plane_length(data);
	convert_textures(data);
	get_color(data);
	draw_image(data);
	mlx_loop(data->mlx);
}

void	draw_image(t_data *data)
{
	int	window_column;

	set_background(data);
	window_column = 0;
	while (window_column < WINDOW_WIDTH)
	{
		ray_vector(window_column, data);
		x_step_size(data);
		y_step_size(data);
		dda(data);
		wall_distance(data);
		draw_column(data, window_column);
		window_column++;
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	ray_vector(int window_column, t_data *data)
{
	double	camera_posx;
	double	camera_planex;
	double	camera_planey;

	camera_posx = 2 * window_column / (double)WINDOW_WIDTH - 1;
	camera_planex = -data->player.player_orienty
		* data->ray_info.camera_plane_length / 2;
	camera_planey = data->player.player_orientx
		* data->ray_info.camera_plane_length / 2;
	data->ray_info.ray_dirx
		= data->player.player_orientx + camera_planex * camera_posx;
	data->ray_info.ray_diry
		= data->player.player_orienty + camera_planey * camera_posx;
}

void	x_step_size(t_data *data)
{
	data->ray_info.wall_x = (int)data->player.player_x;
	data->ray_info.dist_between_xlines = fabs(1 / data->ray_info.ray_dirx);
	if (data->ray_info.ray_dirx < 0)
	{
		data->ray_info.step_x_direct = -1;
		data->ray_info.step_x = (data->player.player_x
				- data->ray_info.wall_x)
			* data->ray_info.dist_between_xlines;
	}
	else
	{
		data->ray_info.step_x_direct = 1;
		data->ray_info.step_x = (data->ray_info.wall_x + 1.0
				- data->player.player_x)
			* data->ray_info.dist_between_xlines;
	}
}

void	y_step_size(t_data *data)
{
	data->ray_info.wall_y = (int)data->player.player_y;
	data->ray_info.dist_between_ylines = fabs(1 / data->ray_info.ray_diry);
	if (data->ray_info.ray_diry < 0)
	{
		data->ray_info.step_y_direct = -1;
		data->ray_info.step_y = (data->player.player_y
				- data->ray_info.wall_y)
			* data->ray_info.dist_between_ylines;
	}
	else
	{
		data->ray_info.step_y_direct = 1;
		data->ray_info.step_y = (data->ray_info.wall_y + 1.0
				- data->player.player_y)
			* data->ray_info.dist_between_ylines;
	}
}

void	dda(t_data *data)
{
	bool	found_wall;

	found_wall = 0;
	while (found_wall == 0)
	{
		if (data->ray_info.step_x < data->ray_info.step_y)
		{
			if (data->map.grid[data->ray_info.wall_y]
				[data->ray_info.wall_x + data->ray_info.step_x_direct] == '1')
			{
				found_wall = 1;
				data->ray_info.horizontal_wall = 0;
				data->ray_info.wall_x += data->ray_info.step_x_direct;
			}
			else
			{
				data->ray_info.step_x += data->ray_info.dist_between_xlines;
				data->ray_info.wall_x += data->ray_info.step_x_direct;
			}
		}
		else
		{
			if (data->map.grid[data->ray_info.wall_y
					+ data->ray_info.step_y_direct]
				[data->ray_info.wall_x] == '1')
			{
				found_wall = 1;
				data->ray_info.horizontal_wall = 1;
				data->ray_info.wall_y += data->ray_info.step_y_direct;
			}
			else
			{
				data->ray_info.step_y += data->ray_info.dist_between_ylines;
				data->ray_info.wall_y += data->ray_info.step_y_direct;
			}
		}
	}
	if (data->ray_info.horizontal_wall == 1)
	{
		if (data->ray_info.step_y_direct == -1)
			data->ray_info.wall_y++;
	}
	else
	{
		if (data->ray_info.step_x_direct == -1)
			data->ray_info.wall_x++;
	}
}

void	wall_distance(t_data *data)
{
	if (data->ray_info.horizontal_wall == 1)
	{
		data->image_info.wall_distance = fabs((data->ray_info.wall_y
					- data->player.player_y) / data->ray_info.ray_diry);
		data->image_info.x_distance = data->ray_info.step_y
			* fabs(data->ray_info.ray_dirx);
		data->image_info.y_distance = 0;
	}
	else
	{
		data->image_info.wall_distance = fabs((data->ray_info.wall_x
					- data->player.player_x) / data->ray_info.ray_dirx);
		data->image_info.y_distance = data->ray_info.step_x
			* fabs(data->ray_info.ray_diry);
		data->image_info.x_distance = 0;
	}
}

// N - E
// E - W
// S - N
// W - S