/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:44:57 by disilva           #+#    #+#             */
/*   Updated: 2024/12/29 20:26:05 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	skip_empty_spaces(int *i, char *line)
{
	while (line[(*i)] == ' ' || line[(*i)] == '	')
		(*i)++;
	return (*i);
}

int	str_end_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	check_png_ending(char *path, int i)
{
	int	fd;

	if (path[i - 1] != 'g' && path[i - 2] != 'n'
		&& path[i - 3] != 'p' && path[i - 4] != '.')
	{
		printf("ERROR\nthe texture file name doesn't end with .png\n");
		return (10);
	}
	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		perror("ERROR\nfile is a directory\n");
		close(fd);
		return (10);
	}
	fd = open(path, O_RDONLY);
	close (fd);
	if (fd == -1)
	{
		perror("ERROR\nerror opening texture file\n");
		return (10);
	}
	return (1);
}

int	process_n_texture(char *line, t_data *data)
{
	int			first_char;
	int			i;
	static int	repetition = 0;

	i = 0;
	i = skip_empty_spaces(&i, line);
	if (line[i] == 'N' && line[++i] == 'O' && line[++i] == ' ')
	{
		repetition++;
		if (repetition > 1)
		{
			printf("ERROR\nmultiple north textures\n");
			return (10);
		}
		first_char = skip_empty_spaces(&i, line);
		i = first_char;
		while (line[i] != '\n')
			i++;
		i--;
		while (line[i]
			== ' ' || line[i] == '	')
			i--;
		line[i + 1] = '\0';
		data->map.n_texture.path = ft_strdup(&(line[first_char]));
		i = str_end_pos(data->map.n_texture.path);
		return (check_png_ending(data->map.n_texture.path, i));
	}
	return (0);
}

int	process_s_texture(char *line, t_data *data)
{
	int			first_char;
	int			i;
	static int	repetition = 0;

	i = 0;
	i = skip_empty_spaces(&i, line);
	if (line[i] == 'S' && line[++i] == 'O' && line[++i] == ' ')
	{
		repetition++;
		if (repetition > 1)
		{
			printf("ERROR\nmultiple south textures\n");
			return (10);
		}
		first_char = skip_empty_spaces(&i, line);
		i = first_char;
		while (line[i] != '\n')
			i++;
		i--;
		while (line[i]
			== ' ' || line[i] == '	')
			i--;
		line[i + 1] = '\0';
		data->map.s_texture.path = ft_strdup(&(line[first_char]));
		i = str_end_pos(data->map.s_texture.path);
		return (check_png_ending(data->map.s_texture.path, i));
	}
	return (0);
}

int	process_w_texture(char *line, t_data *data)
{
	int			first_char;
	int			i;
	static int	repetition = 0;

	i = 0;
	i = skip_empty_spaces(&i, line);
	if (line[i] == 'W' && line[++i] == 'E' && line[++i] == ' ')
	{
		repetition++;
		if (repetition > 1)
		{
			printf("ERROR\nmultiple west textures\n");
			return (10);
		}
		first_char = skip_empty_spaces(&i, line);
		i = first_char;
		while (line[i] != '\n')
			i++;
		i--;
		while (line[i]
			== ' ' || line[i] == '	')
			i--;
		line[i + 1] = '\0';
		data->map.w_texture.path = ft_strdup(&(line[first_char]));
		i = str_end_pos(data->map.w_texture.path);
		return (check_png_ending(data->map.w_texture.path, i));
	}
	return (0);
}

int	process_e_texture(char *line, t_data *data)
{
	int			first_char;
	int			i;
	static int	repetition = 0;

	i = 0;
	i = skip_empty_spaces(&i, line);
	if (line[i] == 'E' && line[++i] == 'A' && line[++i] == ' ')
	{
		repetition++;
		if (repetition > 1)
		{
			printf("ERROR\nmultiple east textures\n");
			return (10);
		}
		first_char = skip_empty_spaces(&i, line);
		i = first_char;
		while (line[i] != '\n')
			i++;
		i--;
		while (line[i]
			== ' ' || line[i] == '	')
			i--;
		line[i + 1] = '\0';
		data->map.e_texture.path = ft_strdup(&(line[first_char]));
		i = str_end_pos(data->map.e_texture.path);
		return (check_png_ending(data->map.e_texture.path, i));
	}
	return (0);
}

bool	process_each_color(int *i, char *line, int *color)
{
	if (line[*i] >= '0' && line[*i] <= '9')
		*color = 0;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		*color = *color * 10 + line[*i] - '0';
		(*i)++;
	}
	if ((*color != -1 && line[*i] == ',' && *color <= 255)
		|| (*color != -2 && (line[*i] == '\n' || line[*i] == ' ')
			&& *color <= 255))
		return (0);
	printf("ERROR\ncolor outside of range\n");
	return (1);
}

int	process_floor_color(char *line, t_data *data)
{
	int			i;
	static int	repetition = 0;

	i = 0;
	i = skip_empty_spaces(&i, line);
	if (line[i] == 'F' && line[++i] == ' ')
	{
		repetition++;
		if (repetition > 1)
		{
			printf("ERROR\nmultiple floor colors\n");
			return (10);
		}
		while (line[i] == ' ' || line[i] == '	')
			i++;
		if (process_each_color(&i, line, &data->map.floor_color.red) == 1)
			return (10);
		i++;
		if (process_each_color(&i, line, &data->map.floor_color.green) == 1)
			return (10);
		i++;
		if (process_each_color(&i, line, &data->map.floor_color.blue) == 1)
			return (10);
		return (1);
	}
	return (0);
}

int	process_celing_color(char *line, t_data *data)
{
	int			i;
	static int	repetition = 0;

	i = 0;
	i = skip_empty_spaces(&i, line);
	if (line[i] == 'C' && line[++i] == ' ')
	{
		repetition++;
		if (repetition > 1)
		{
			printf("ERROR\nmultiple celling colors\n");
			return (10);
		}
		while (line[i] == ' ' || line[i] == '	')
			i++;
		if (process_each_color(&i, line, &data->map.celing_color.red) == 1)
			return (10);
		i++;
		if (process_each_color(&i, line, &data->map.celing_color.green) == 1)
			return (10);
		i++;
		if (process_each_color(&i, line, &data->map.celing_color.blue) == 1)
			return (10);
		return (1);
	}
	return (20);
}
