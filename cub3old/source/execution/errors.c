/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:53:35 by diogofms          #+#    #+#             */
/*   Updated: 2024/12/31 01:51:27 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_mlx_error(t_data data)
{
	if (data.mlx == 0)
	{
		perror("ERROR\nfailure to set up graphical environment\n");
		exit (1);
	}
}

void	ft_img_error(t_data data)
{
	if (data.img == 0)
	{
		mlx_close_window(data.mlx);
		perror("ERROR\nfailure to create image\n");
		exit (1);
	}
}
