/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:46:00 by disilva           #+#    #+#             */
/*   Updated: 2024/05/31 01:56:21 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_end_conditions1(struct s_variables *var)
{
	if (var->line[var->i - 1] == '\n')
		return (2);
	return (1);
}

int	check_end_conditions2(struct s_variables *var, int *byte_size,
									int fd, char *buffer)
{
	*byte_size = read(fd, buffer, BUFFER_SIZE);
	if (*byte_size < 0)
	{
		free (var->line);
		return (0);
	}
	return (1);
}
