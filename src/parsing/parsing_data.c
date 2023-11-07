#include "../../include/parsing.h"

static int	set_color(int color, char **map, t_data *data)
{
	if (color >= 0 && color <= 255)
		return (color);
	else
		ft_exit_parsing("color out of range", map, data);
	return (0);
}

static t_data	*get_c_floor(char *str, char **map, t_data *data)
{
	char	**split_color;
	char	*tmp;

	if (count_char(str, ',') != 2)
		ft_exit_parsing("wrong data for F", map, data);
	tmp = del_space(ft_strdup(str + 1));
	split_color = ft_split(tmp, ',');
	if (!split_color[0] || !split_color[1] || !split_color[2] \
	|| split_color[0][0] == -62 || split_color[1][0] == -62 \
	|| split_color[2][0] == -62 || ft_strlen(split_color[0]) > 3 \
	|| ft_strlen(split_color[1]) > 3 || ft_strlen(split_color[2]) > 3)
	{
		ft_xfree(tmp);
		ft_free_null(split_color);
		ft_exit_parsing("F color out of range", map, data);
	}
	data->c_floor.r = set_color(ft_atoi(split_color[0]), map, data);
	data->c_floor.g = set_color(ft_atoi(split_color[1]), map, data);
	data->c_floor.b = set_color(ft_atoi(split_color[2]), map, data);
	ft_xfree(tmp);
	ft_free_null(split_color);
	data->c_floor.set = 1;
	return (data);
}

static t_data	*get_c_sky(char *str, char **map, t_data *data)
{
	char	**split_color;
	char	*tmp;

	if (count_char(str, ',') != 2)
		ft_exit_parsing("wrong data for C", map, data);
	tmp = del_space(ft_strdup(str + 1));
	split_color = ft_split(tmp, ',');
	if (!split_color[0] || !split_color[1] || !split_color[2] \
	|| split_color[0][0] == -62 || split_color[1][0] == -62 \
	|| split_color[2][0] == -62 || ft_strlen(split_color[0]) > 3 \
	|| ft_strlen(split_color[1]) > 3 || ft_strlen(split_color[2]) > 3)
	{
		ft_xfree(tmp);
		ft_free_null(split_color);
		ft_exit_parsing("C color out of range", map, data);
	}
	data->c_sky.r = set_color(ft_atoi(split_color[0]), map, data);
	data->c_sky.g = set_color(ft_atoi(split_color[1]), map, data);
	data->c_sky.b = set_color(ft_atoi(split_color[2]), map, data);
	ft_xfree(tmp);
	ft_free_null(split_color);
	data->c_sky.set = 1;
	return (data);
}

static t_data	*get_color(char *str, char **map, t_data *data)
{
	if (!ft_strcmp_until_space(str, "F"))
	{
		if (!data->c_floor.set)
			data = get_c_floor(str, map, data);
		else
			ft_exit_parsing("2 F", map, data);
	}
	else if (!ft_strcmp_until_space(str, "C"))
	{
		if (!data->c_sky.set)
			data = get_c_sky(str, map, data);
		else
			ft_exit_parsing("2 C", map, data);
	}
	return (data);
}

t_data	*get_sprite(char *sprite, char **map, t_data *data)
{
	if (!ft_strcmp_until_space(sprite, "NO"))
	{
		if (data->north.path)
			ft_exit_parsing("2 NO", map, data);
		data->north.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until_space(sprite, "SO"))
	{
		if (data->south.path)
			ft_exit_parsing("2 SO", map, data);
		data->south.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until_space(sprite, "EA"))
	{
		if (data->east.path)
			ft_exit_parsing("2 EA", map, data);
		data->east.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until_space(sprite, "WE"))
	{
		if (data->west.path)
			ft_exit_parsing("2 WE", map, data);
		data->west.path = del_space(ft_strdup(sprite + 2));
	}
	return (get_color(sprite, map, data));
}
