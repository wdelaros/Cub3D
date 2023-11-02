#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_sprite
{
	char		*path;
	mlx_image_t	*img;
}	t_sprite;

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_data
{
	char		**floor;
	char		**wall;
	char		**sky;
	t_color		c_floor;
	t_color		c_sky;
	t_pos		hero;
	t_sprite	north;
	t_sprite	south;
	t_sprite	west;
	t_sprite	east;
}	t_data;

#endif