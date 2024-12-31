/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:35:47 by disilva           #+#    #+#             */
/*   Updated: 2024/12/31 01:26:33 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define WINDOW_WIDTH 1200
# define WINDOW_LENGTH 600
# define FOV 60
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_texture
{
	mlx_texture_t	*texture;
	char			*path;

}	t_texture;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;

}	t_color;

typedef struct s_map_grid
{
	char				*line;
	int					line_size;
	struct s_map_grid	*next;

}	t_map_grid;

typedef struct s_map
{
	char		**grid;
	int			map_width;
	int			map_length;
	t_texture	n_texture;
	t_texture	w_texture;
	t_texture	e_texture;
	t_texture	s_texture;
	t_color		celing_color;
	t_color		floor_color;
}	t_map;

typedef struct s_player
{
	float	player_x;
	float	player_y;
	float	player_orientx;
	float	player_orienty;
	int		angle;
}	t_player;

typedef struct s_ray_info
{
	double	ray_dirx;
	double	ray_diry;
	double	dist_between_xlines;
	double	dist_between_ylines;
	double	step_x;
	double	step_y;
	int		step_x_direct;
	int		step_y_direct;
	int		wall_x;
	int		wall_y;
	bool	horizontal_wall;
	double	camera_plane_length;
}	t_ray_info;

typedef struct s_image_info
{
	double	wall_distance;
	int		floor_color;
	int		celing_color;
	double	x_distance;
	double	y_distance;
}	t_image_info;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			map;
	t_player		player;
	t_ray_info		ray_info;
	t_image_info	image_info;
}	t_data;

int		check_param(int argc, char **argv);
bool	parse_map_file(t_data *data, char *file_name);
bool	check_empty_line(char *line);
int		process_n_texture(char *line, t_data *data);
int		process_s_texture(char *line, t_data *data);
int		process_w_texture(char *line, t_data *data);
int		process_e_texture(char *line, t_data *data);
int		process_floor_color(char *line, t_data *data);
int		process_celing_color(char *line, t_data *data);
bool	process_map(int fd, t_data *data, char *line);
void	free_textures(t_data *data);
void	free_map(t_data *data, int i);
bool	check_empty_line(char *line);
void	esc_hook(mlx_key_data_t key, void *param);
void	check_movement(void *data);
void	convert_textures(t_data *data);
void	ft_mlx_error(t_data data);
void	ft_img_error(t_data data);
void	run_game(t_data *data);
void	draw_column(t_data *data, int x_cord);
void	draw_image(t_data *data);
void	set_background(t_data *data);
void	get_color(t_data *data);

#endif
