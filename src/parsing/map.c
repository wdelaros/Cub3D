#include "../../include/parsing.h"

static int	is_map(char	*str)
{
	if (ft_find_first_alphanum(str) == '1' || \
	ft_find_first_alphanum(str) == '0')
		return (1);
	return (0);
}

static int	is_correct_data(char *str)
{
	if (!ft_strcmp_until_space(str, "NO") || !ft_strcmp_until_space(str, "SO") \
	|| !ft_strcmp_until_space(str, "EA") || !ft_strcmp_until_space(str, "WE") \
	|| !ft_strcmp_until_space(str, "F") || !ft_strcmp_until_space(str, "C") \
	|| !ft_strcmp(str, "\r") || !ft_strcmp(str, "\0"))
		return (1);
	return (0);
}

static t_data	*parse_map(t_data *data, char **map, int i)
{
	while (map[i])
	{
		ft_printf("Cub3D map[%d]	: %s\n", i, map[i]);
		i++;
	}
	return (data);
}

t_data	*parse_file(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		if (is_map(map[i]))
			break ;
		map[i] = del_space(map[i]);
		if (is_correct_data(map[i]))
			data = get_sprite(map[i], map, data);
		else
			ft_exit_parsing("Wrong identifier", map, data);
		ft_printf("file[%d]	: %s\n", i, map[i]);
		i++;
	}
	if (!data->c_floor.set || !data->c_sky.set || !data->north.path \
		|| !data->south.path || !data->east.path || !data->west.path)
		ft_exit_parsing("missing information", map, data);
	else
		data = parse_map(data, map, i);
	return (data);
}
