/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:38:18 by disilva           #+#    #+#             */
/*   Updated: 2024/12/31 01:54:16 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	print_map_file(t_data	*data)
{
	int	i;

	printf ("n%s\n", data->map.n_texture.path);
	printf ("w%s\n", data->map.w_texture.path);
	printf ("e%s\n", data->map.e_texture.path);
	printf ("s%s\n", data->map.s_texture.path);
	printf ("c%d%d%d\n", data->map.celing_color.red,
		data->map.celing_color.green, data->map.celing_color.blue);
	printf ("f%d%d%d\n", data->map.floor_color.red,
		data->map.floor_color.green, data->map.floor_color.blue);
	printf("%d %d\n", data->map.map_length, data->map.map_width);
	i = 0;
	while (i < data->map.map_length)
	{
		printf ("%s\n", data->map.grid[i]);
		i++;
	}
	// free_map(data, data->map.map_length);
	// free_textures(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_param(argc, argv))
		return (1);
	if (parse_map_file(&data, argv[1]))
		return (1);
	// print_map_file(&data);
	run_game(&data);
	return (0);
}
