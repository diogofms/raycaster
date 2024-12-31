/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:08:45 by disilva           #+#    #+#             */
/*   Updated: 2024/12/29 20:26:01 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	init_map_data_struct(t_data *data)
{
	data->map.grid = NULL;
	data->map.map_width = -1;
	data->map.map_length = -1;
	data->map.n_texture.path = NULL;
	data->map.w_texture.path = NULL;
	data->map.e_texture.path = NULL;
	data->map.s_texture.path = NULL;
	data->map.celing_color.red = -1;
	data->map.celing_color.green = -1;
	data->map.celing_color.blue = -2;
	data->map.floor_color.red = -1;
	data->map.floor_color.green = -1;
	data->map.floor_color.blue = -2;
	data->player.player_x = -1;
	data->player.player_y = -1;
	data->player.player_orientx = -1;
	data->player.player_orienty = -1;
}

bool	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '	')
			return (false);
		i++;
	}
	return (true);
}

int	process_line_until_map(char *line, t_data *data)
{
	static int	found_line = 0;
	int			_return;

	_return = process_n_texture(line, data);
	if (_return == 1)
		return (++found_line);
	else if (_return == 10)
		return (10);
	_return = process_s_texture(line, data);
	if (_return == 1)
		return (++found_line);
	else if (_return == 10)
		return (10);
	_return = process_w_texture(line, data);
	if (_return == 1)
		return (++found_line);
	else if (_return == 10)
		return (10);
	_return = process_e_texture(line, data);
	if (_return == 1)
		return (++found_line);
	else if (_return == 10)
		return (10);
	_return = process_floor_color(line, data);
	if (_return == 1)
		return (++found_line);
	else if (_return == 10)
		return (10);
	_return = process_celing_color(line, data);
	if (_return == 1)
		return (++found_line);
	else if (_return == 10 || _return == 20)
		return (_return);
	if (found_line == 6)
		return (found_line);
	return (0);
}

void	free_textures(t_data *data)
{
	if (data->map.n_texture.path != NULL)
		free (data->map.n_texture.path);
	if (data->map.s_texture.path != NULL)
		free (data->map.s_texture.path);
	if (data->map.w_texture.path != NULL)
		free (data->map.w_texture.path);
	if (data->map.e_texture.path != NULL)
		free (data->map.e_texture.path);
}

char	*skip_until_map(char *line, int fd)
{
	int	i;

	free(line);
	line = get_next_line(fd);
	i = 0;
	while (1)
	{
		while (line[i] != '\n' && line[i] != '\0')
		{
			if (line[i] != ' ' && line[i] != '	')
				return (line);
			i++;
		}
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (NULL);
	}
	return (NULL);
}

bool	parse_map_file(t_data *data, char *file_name)
{
	int		fd;
	char	*line;
	int		info;
	bool	map_has_content;

	fd = open(file_name, O_DIRECTORY);
	if (fd >= 0)
	{
		perror("ERROR\nfile is a directory\n");
		close(fd);
		return (1);
	}
	init_map_data_struct(data);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR\nerror opening file\n");
		return (1);
	}
	map_has_content = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!check_empty_line(line))
		{
			map_has_content = 1;
			info = process_line_until_map(line, data);
			if (info == 6)
				break ;
			else if (info == 0 || info == 10 || info == 20)
			{
				if (info == 20)
					printf("ERROR\nunrecognizable line\n");
				free (line);
				free_textures(data);
				close(fd);
				return (1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	if (info < 6)
	{
		printf("ERROR\ninfo missing\n");
		free_textures(data);
		close(fd);
		return (1);
	}
	if (map_has_content == 0)
	{
		printf("ERROR\nfile is empty\n");
		return (1);
	}
	line = skip_until_map(line, fd);
	if (line == NULL)
	{
		printf("ERROR\nthere is no map\n");
		free_textures(data);
		close(fd);
		return (1);
	}
	return (process_map(fd, data, line));
}
