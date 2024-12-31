/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogofms <diogofms@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:09:54 by disilva           #+#    #+#             */
/*   Updated: 2024/12/23 01:26:35 by diogofms         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	check_param(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		printf("ERROR\nwrong number of parameters\n");
		return (1);
	}
	i = 0;
	while (argv[1][i] != '\0')
		i++;
	i = i - 4;
	if (!(argv[1][i] == '.' && argv[1][i + 1] == 'c'
		&& argv[1][i + 2] == 'u' && argv[1][i + 3] == 'b'))
	{
		printf("ERROR\nthe map name does not terminate correctly\n");
		return (1);
	}
	return (0);
}
