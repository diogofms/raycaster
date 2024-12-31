/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:38:44 by disilva           #+#    #+#             */
/*   Updated: 2024/03/13 01:29:22 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int ascii)
{
	if (ascii > -1 && ascii < 128)
		return (1);
	else
		return (0);
}
