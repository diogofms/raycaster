/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 01:30:19 by diogofms          #+#    #+#             */
/*   Updated: 2024/12/31 01:50:53 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	calculate_new_orientation(t_data *data)
{
	data->player.player_orientx = cos(data->player.angle * M_PI / 180);
	data->player.player_orienty = sin(data->player.angle * M_PI / 180);
}

void	check_wall(t_data *data, double next_x_pos, double next_y_pos)
{
	if (data->map.grid[(int)next_y_pos][(int)next_x_pos] != '1')
	{
		data->player.player_x = next_x_pos;
		data->player.player_y = next_y_pos;
		return ;
	}
	if (data->map.grid[(int)data->player.player_y][(int)next_x_pos] != '1')
		data->player.player_x = next_x_pos;
	else if (data->map.grid[(int)next_y_pos][(int)data->player.player_x] != '1')
		data->player.player_y = next_y_pos;
}

void	check_movement_part3(t_data *data)
{
	double	next_x_pos;
	double	next_y_pos;

	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		next_x_pos = data->player.player_x - data->player.player_orientx * 0.07;
		next_y_pos = data->player.player_y - data->player.player_orienty * 0.07;
		check_wall(data, next_x_pos, next_y_pos);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		next_x_pos = data->player.player_x - data->player.player_orienty * 0.07;
		next_y_pos = data->player.player_y + data->player.player_orientx * 0.07;
		check_wall(data, next_x_pos, next_y_pos);
	}
	draw_image(data);
}

void	check_movement_part2(t_data *data)
{
	double	next_x_pos;
	double	next_y_pos;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		next_x_pos = data->player.player_x + data->player.player_orientx * 0.07;
		next_y_pos = data->player.player_y + data->player.player_orienty * 0.07;
		check_wall(data, next_x_pos, next_y_pos);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		next_x_pos = data->player.player_x + data->player.player_orienty * 0.07;
		next_y_pos = data->player.player_y - data->player.player_orientx * 0.07;
		check_wall(data, next_x_pos, next_y_pos);
	}
	check_movement_part3(data);
}

void	check_movement(void *_data)
{
	t_data	*data;

	data = (t_data *)_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.angle += 2;
		if (data->player.angle < 0)
			data->player.angle += 360;
		calculate_new_orientation(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.angle -= 2;
		if (data->player.angle > 360)
			data->player.angle -= 360;
		calculate_new_orientation(data);
	}
	check_movement_part2(data);
}
