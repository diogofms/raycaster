/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 01:03:01 by diogofms          #+#    #+#             */
/*   Updated: 2024/12/31 01:41:05 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	esc_hook(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.action != MLX_PRESS && key.action != MLX_REPEAT)
		return ;
	if (key.key == MLX_KEY_ESCAPE)
	{
		free_textures(data);
		free_map(data, data->map.map_length);
		mlx_delete_image(data->mlx, data->img);
		mlx_close_window(data->mlx);
		exit(0);
	}
}
