#include "../../include/parsing.h"

//to finish
static int	set_color(int color, t_data *data)
{

	if (color >= 0 && color <= 255)
		return (color);
	else
		ft_exit_parsing("Error\ncolor out of range", data);
	return (0);
}

static t_data	*get_color(char *str, t_data *data)
{
	char	**split_color;
	char	*tmp;

	if (!ft_strcmp_until(str, "F", ' '))
	{
		if (!data->c_floor.set)
		{
			tmp = del_space(ft_strdup(str + 1));
			split_color = ft_split(tmp, ',');
			data->c_floor.r = set_color(ft_atoi(split_color[0]), data);
			data->c_floor.g = set_color(ft_atoi(split_color[1]), data);
			data->c_floor.b = set_color(ft_atoi(split_color[2]), data);
			ft_xfree(tmp);
			ft_free_null(split_color);
			data->c_floor.set = 1;
		}
		else
			ft_exit_parsing("Error\n2 F", data);
	}
	else if (!ft_strcmp_until(str, "C", ' '))
	{
		if (!data->c_sky.set)
		{
			tmp = del_space(ft_strdup(str + 1));
			split_color = ft_split(tmp, ',');
			data->c_sky.r = set_color(ft_atoi(split_color[0]), data);
			data->c_sky.g = set_color(ft_atoi(split_color[1]), data);
			data->c_sky.b = set_color(ft_atoi(split_color[2]), data);
			ft_xfree(tmp);
			ft_free_null(split_color);
			data->c_sky.set = 1;
		}
		else
			ft_exit_parsing("Error\n2 C", data);
	}
	return (data);
}

static t_data	*get_sprite(char *sprite, t_data *data)
{
	if (!ft_strcmp_until(sprite, "NO", ' '))
	{
		if (data->north.path)
			ft_exit_parsing("Error\n2 NO", data);
		data->north.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until(sprite, "SO", ' '))
	{
		if (data->south.path)
			ft_exit_parsing("Error\n2 SO", data);
		data->south.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until(sprite, "EA", ' '))
	{
		if (data->east.path)
			ft_exit_parsing("Error\n2 EA", data);
		data->east.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until(sprite, "WE", ' '))
	{
		if (data->west.path)
			ft_exit_parsing("Error\n2 WE", data);
		data->west.path = del_space(ft_strdup(sprite + 2));
	}
	return (get_color(sprite, data));
}

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_data	*parse_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->floor && data->floor[i])
	{
		data->floor[i] = del_space(data->floor[i]);
		data = get_sprite(data->floor[i], data);
		ft_printf("map[%d]	: %s\n", i, data->floor[i]);
		i++;
	}
	return (data);
}
