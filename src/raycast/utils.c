/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:51:43 by brheaume          #+#    #+#             */
/*   Updated: 2023/12/08 15:51:44 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycast.h"

uint32_t	ft_rgba_to_uint(double r, double g, double b)
{
	return ((r * 16777216) + (g * 65536) + (b * 256) + 0xFF);
}

int	**ft_xpm_convert(xpm_t *xpm)
{
	int	**conv;
	int	x;
	int	y;

	conv = ft_calloc(xpm->texture.height + 1, sizeof(int *));
	y = BASE - 1;
	while (++y < (int)(xpm->texture.height + BASE))
	{
		x = BASE - 1;
		conv[y - BASE] = ft_calloc(xpm->texture.width, sizeof(int));
		while (++x < (int)(xpm->texture.width + BASE))
		{
			conv[y - BASE][x - BASE] = ft_rgba_to_uint(
					xpm->texture.pixels[(xpm->texture.width * BASE \
						* (y - BASE)) + (BASE * (x - BASE))],
					xpm->texture.pixels[(xpm->texture.width * BASE \
						* (y - BASE)) + (BASE * (x - BASE)) + 1],
					xpm->texture.pixels[(xpm->texture.width * BASE \
						* (y - BASE)) + (BASE * (x - BASE)) + 2]);
		}
	}
	return (conv);
}
