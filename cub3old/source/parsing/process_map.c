/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:31:13 by disilva           #+#    #+#             */
/*   Updated: 2024/12/31 01:58:24 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	line_length(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	return (i);
}

void	free_struct(t_map_grid *map)
{
	t_map_grid	*next;

	next = map;
	while (next->next)
	{
		next = map->next;
		free (map->line);
		free (map);
		map = next;
	}
	free(map);
}

void	free_map(t_data *data, int i)
{
	while (i > 0)
	{
		i--;
		free (data->map.grid[i]);
	}
	free (data->map.grid);
}

char	*copy_until_new_line(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

bool	copy_map_to_array(t_map_grid *map, t_data *data)
{
	int			i;
	t_map_grid	*next;

	next = map;
	data->map.grid = malloc((data->map.map_length + 1) * sizeof(char *));
	if (!data->map.grid)
	{
		perror("ERROR\nerror allocating memory\n");
		return (1);
	}
	i = 0;
	while (next->next)
	{
		if (next->line_size > data->map.map_width)
			data->map.map_width = next->line_size;
		data->map.grid[i] = malloc(next->line_size + 1);
		if (!data->map.grid[i])
		{
			free_map(data, i);
			perror("ERROR\nerror allocating memory\n");
			return (1);
		}
		data->map.grid[i] = copy_until_new_line(data->map.grid[i], next->line);
		i++;
		next = next->next;
	}
	data->map.grid[i] = NULL;
	return (0);
}

void	player_orientation(char player, t_data *data)
{
	if (player == 'N')
	{
		data->player.angle = 270;
		data->player.player_orientx = 0;
		data->player.player_orienty = -1;
	}
	else if (player == 'S')
	{
		data->player.angle = 90;
		data->player.player_orientx = 0;
		data->player.player_orienty = 1;
	}
	else if (player == 'W')
	{
		data->player.angle = 180;
		data->player.player_orientx = -1;
		data->player.player_orienty = 0;
	}
	else if (player == 'E')
	{
		data->player.angle = 0;
		data->player.player_orientx = 1;
		data->player.player_orienty = 0;
	}
}

bool	check_each_element(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < data->map.map_length)
	{
		j = 0;
		while (data->map.grid[i][j] != '\0')
		{
			if (data->map.grid[i][j] != '1' && data->map.grid[i][j] != '0'
			&& data->map.grid[i][j] != ' ' && data->map.grid[i][j] != 'N'
			&& data->map.grid[i][j] != 'S' && data->map.grid[i][j] != 'E'
			&& data->map.grid[i][j] != 'W')
			{
				printf("ERROR\nthe map has an invalid character\n");
				return (1);
			}
			if (data->map.grid[i][j] == 'N' || data->map.grid[i][j] == 'S'
			|| data->map.grid[i][j] == 'E' || data->map.grid[i][j] == 'W')
			{
				player_count++;
				player_orientation(data->map.grid[i][j], data);
				data->player.player_x = j + 0.5;
				data->player.player_y = i + 0.5;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("ERROR\nthe map has an incorrect amount of players\n");
		return (1);
	}
	return (0);
}

bool	check_if_closed(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.map_length)
	{
		j = 0;
		while (data->map.grid[i][j] != '\0')
		{
			if (data->map.grid[i][j] != '1' && data->map.grid[i][j] != ' ')
			{
				if (i == 0 || i == data->map.map_length - 1
					|| j == 0 || data->map.grid[i][j + 1] == '\0'
					|| data->map.grid[i - 1][j] == ' '
					|| data->map.grid[i + 1][j] == ' '
					|| data->map.grid[i][j - 1] == ' '
					|| data->map.grid[i][j + 1] == ' ')
				{
					printf("ERROR\nthe map is not closed\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

bool	check_map_config(t_data *data, int fd)
{
	if (check_each_element(data))
	{
		free_map(data, data->map.map_length);
		free_textures(data);
		close(fd);
		return (1);
	}
	if (check_if_closed(data))
	{
		free_map(data, data->map.map_length);
		free_textures(data);
		close(fd);
		return (1);
	}
	return (0);
}

bool	process_map(int fd, t_data *data, char *line)
{
	t_map_grid	*map;
	t_map_grid	*next;
	bool		empty_line;

	(void)data;
	map = malloc(sizeof(t_map_grid));
	if (!map)
	{
		free (line);
		close(fd);
		perror("ERROR\nerror allocating memory\n");
		return (1);
	}
	next = map;
	data->map.map_length = 0;
	empty_line = false;
	while (line)
	{
		if (empty_line == 0)
			empty_line = check_empty_line(line);
		if (check_empty_line(line))
			free (line);
		else
		{
			if (empty_line == 1)
			{
				free_struct(map);
				free_textures(data);
				close(fd);
				free (line);
				printf("ERROR\nempty line in the middle of the map\n");
				return (1);
			}
			data->map.map_length++;
			next->line = line;
			next->line_size = line_length(line);
			next->next = malloc(sizeof(t_map_grid));
			if (!next->next)
			{
				free_struct(map);
				free_textures(data);
				close(fd);
				free (line);
				perror("ERROR\nerror allocating memory\n");
				return (1);
			}
			next = next->next;
			next->next = NULL;
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (copy_map_to_array(map, data))
	{
		free_struct(map);
		return (1);
	}
	free_struct(map);
	return (check_map_config(data, fd));
}
