/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:43:19 by disilva           #+#    #+#             */
/*   Updated: 2024/05/31 01:56:19 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	initial_checks(int *byte_size, int fd,
							int *last_position, char *buffer)
{
	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	if (*last_position == 0)
		*byte_size = read(fd, buffer, BUFFER_SIZE);
	if (*byte_size <= 0)
	{
		if (buffer[*last_position -1] != '9')
			*last_position = 0;
		return (0);
	}
	return (1);
}

static char	*extend_line(int line_size, char *line)
{
	char	*linecpy;
	int		i;

	linecpy = malloc(line_size + BUFFER_SIZE);
	if (linecpy == NULL)
	{
		free (line);
		return (NULL);
	}
	i = 0;
	while (i < line_size)
	{
		linecpy[i] = line[i];
		i++;
	}
	free (line);
	return (linecpy);
}

static void	cpybuffer_to_linecpy(char *buffer, int *last_position,
									int *byte_size, struct s_variables *var)
{
	var->i = 0;
	while (buffer[*last_position] != '\n' && *byte_size > 1)
	{
		var->linecpy[var->line_size + var->i] = buffer[*last_position];
		(*last_position)++;
		var->i++;
		(*byte_size)--;
	}
	var->linecpy[var->line_size + var->i] = buffer[*last_position];
	(*last_position)++;
	var->i++;
	(*byte_size)--;
}

static int	cpylinecpy_to_line(struct s_variables *var, int *byte_size,
								int *last_position)
{
	var->line_size = var->line_size + var->i;
	var->line = malloc(var->line_size + 1);
	if (var->line == NULL)
	{
		free (var->linecpy);
		return (0);
	}
	var->i = 0;
	while (var->i < var->line_size)
	{
		var->line[var->i] = var->linecpy[var->i];
		var->i++;
	}
	var->line[var->i] = '\0';
	free (var->linecpy);
	if (*byte_size == 0)
		*last_position = 0;
	return (1);
}

char	*get_next_line(int fd)
{
	static char			buffer[BUFFER_SIZE];
	static int			byte_size = 0;
	static int			last_position = 0;
	struct s_variables	var;

	if (initial_checks(&byte_size, fd, &last_position, buffer) == 0)
		return (NULL);
	var.line_size = 0;
	var.line = malloc(1);
	if (var.line == NULL)
		return (NULL);
	while (byte_size > 0)
	{
		var.linecpy = extend_line(var.line_size, var.line);
		if (var.linecpy == NULL)
			return (NULL);
		cpybuffer_to_linecpy(buffer, &last_position, &byte_size, &var);
		if (cpylinecpy_to_line(&var, &byte_size, &last_position) == 0)
			return (NULL);
		if (check_end_conditions1(&var) == 2)
			break ;
		else if (check_end_conditions2(&var, &byte_size, fd, buffer) == 0)
			return (NULL);
	}
	return (var.line);
}
