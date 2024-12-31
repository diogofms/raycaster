/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:44:56 by diogofms          #+#    #+#             */
/*   Updated: 2024/12/31 01:58:10 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	texture_pixel_color(double x, double y, mlx_texture_t *texture);

void	get_color(t_data *data)
{
	data->image_info.celing_color = (int)((data->map.celing_color.red << 24)
			| (data->map.celing_color.green << 16)
			| (data->map.celing_color.blue << 8)
			| 0xFF);
	data->image_info.floor_color = (int)((data->map.floor_color.red << 24)
			| (data->map.floor_color.green << 16)
			| (data->map.floor_color.blue << 8)
			| 0xFF);
}

void	convert_textures(t_data *data)
{
	data->map.n_texture.texture = mlx_load_png(data->map.n_texture.path);
	data->map.s_texture.texture = mlx_load_png(data->map.s_texture.path);
	data->map.e_texture.texture = mlx_load_png(data->map.e_texture.path);
	data->map.w_texture.texture = mlx_load_png(data->map.w_texture.path);
	if (!data->map.n_texture.texture || !data->map.s_texture.texture
		|| !data->map.e_texture.texture || !data->map.w_texture.texture)
	{
		perror ("ERROR\nfailure to load textures\n");
		free_textures(data);
		free_map(data, data->map.map_length);
		mlx_delete_image(data->mlx, data->img);
		mlx_close_window(data->mlx);
		exit (0);
	}
}

void	set_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_LENGTH / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(data->img, x, y, data->image_info.celing_color);
			x++;
		}
		y++;
	}
	while (y < WINDOW_LENGTH)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(data->img, x, y, data->image_info.floor_color);
			x++;
		}
		y++;
	}
}

void	draw_column(t_data *data, int x_cord)
{
	int				wall_heigth;
	int				wall_bottom;
	int				wall_top;
	int				y_cord;
	double			wall_x_cord;
	double			wall_y_cord;
	double			pixel_step_y;
	mlx_texture_t	*texture;

	wall_heigth = (int)(WINDOW_LENGTH / data->image_info.wall_distance);
	if (data->ray_info.horizontal_wall == 1)
	{
		if (data->ray_info.step_y_direct == 1)
		{
			wall_x_cord = data->player.player_x + data->image_info.x_distance
				* data->ray_info.step_x_direct;
			wall_x_cord = (1 - fmod(wall_x_cord, 1.0))
				* data->map.s_texture.texture->width;
			pixel_step_y = data->map.s_texture.texture->height
				/ (double)wall_heigth;
			texture = data->map.s_texture.texture;
		}
		else
		{
			wall_x_cord = data->player.player_x + data->image_info.x_distance
				* data->ray_info.step_x_direct;
			wall_x_cord = (fmod(wall_x_cord, 1.0))
				* data->map.n_texture.texture->width;
			pixel_step_y = data->map.n_texture.texture->height
				/ (double)wall_heigth;
			texture = data->map.n_texture.texture;
		}
	}
	else
	{
		if (data->ray_info.step_x_direct == 1)
		{
			wall_x_cord = data->player.player_y + data->image_info.y_distance
				* data->ray_info.step_y_direct;
			wall_x_cord = (fmod(wall_x_cord, 1.0))
				* data->map.e_texture.texture->width;
			pixel_step_y = data->map.e_texture.texture->height
				/ (double)wall_heigth;
			texture = data->map.e_texture.texture;
		}
		else
		{
			wall_x_cord = data->player.player_y + data->image_info.y_distance
				* data->ray_info.step_y_direct;
			wall_x_cord = (1 - fmod(wall_x_cord, 1.0))
				* data->map.w_texture.texture->width;
			pixel_step_y = data->map.w_texture.texture->height
				/ (double)wall_heigth;
			texture = data->map.w_texture.texture;
		}
	}
	wall_top = -wall_heigth / 2 + WINDOW_LENGTH / 2;
	wall_bottom = wall_heigth / 2 + WINDOW_LENGTH / 2;
	if (wall_bottom < WINDOW_LENGTH)
	{
		y_cord = wall_bottom - 1;
		wall_y_cord = texture->height - 1;
	}
	else
	{
		y_cord = WINDOW_LENGTH - 1;
		wall_y_cord = texture->height
			- ((wall_bottom - WINDOW_LENGTH) * pixel_step_y) - 1;
		wall_top = 0;
	}
	while (y_cord >= wall_top)
	{
		mlx_put_pixel(data->img, x_cord, y_cord,
			texture_pixel_color(wall_x_cord, wall_y_cord, texture));
		wall_y_cord -= pixel_step_y;
		y_cord--;
	}
}

int	texture_pixel_color(double x, double y, mlx_texture_t *texture)
{
	int	color;
	int	red;
	int	green;
	int	blue;
	int	a;

	x = (int)(x) % texture->width;
	y = (int)(y) % texture->height;
	red = texture->pixels[((int)y * texture->width + (int)x) * 4];
	green = texture->pixels[((int)y * texture->width + (int)x) * 4 + 1];
	blue = texture->pixels[((int)y * texture->width + (int)x) * 4 + 2];
	a = texture->pixels[((int)y * texture->width + (int)x) * 4 + 3];
	color = red << 24 | green << 16 | blue << 8 | a;
	return (color);
}
