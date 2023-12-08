/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:51:18 by brheaume          #+#    #+#             */
/*   Updated: 2023/12/08 15:51:18 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/error.h"

void	ft_error_interrupt(t_data *data)
{
	if (data->north.img)
		mlx_delete_xpm42(data->north.img);
	if (data->south.img)
		mlx_delete_xpm42(data->south.img);
	if (data->east.img)
		mlx_delete_xpm42(data->east.img);
	if (data->west.img)
		mlx_delete_xpm42(data->west.img);
	ft_free_null(data->wall);
	ft_free_null((char **)data->map);
	ft_free_null((char **)data->north.pxl);
	ft_free_null((char **)data->south.pxl);
	ft_free_null((char **)data->east.pxl);
	ft_free_null((char **)data->west.pxl);
	ft_xfree(data->north.path);
	ft_xfree(data->south.path);
	ft_xfree(data->east.path);
	ft_xfree(data->west.path);
	ft_putendl_fd("Interrupted!", ERROR_OUTPUT);
	mlx_terminate(data->mlx);
	exit(EXIT_FAILURE);
}
