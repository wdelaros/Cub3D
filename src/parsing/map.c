#include "../../include/parsing.h"

char	*del_space(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str && (str[i] == ' ' /*|| str[i] == '	'*/))
		i++;
	res = ft_strdup(str + i);
	return (free(str), res);
}

int	ft_strcmp_until(const char *s1, const char *s2, char c)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] == s2[i] && (s1[i + 1] != c || s2[i + 1]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//to finish
static int	set_color(int color)
{

	if (color >= 0 && color <= 255)
		return (color);
	else
	{
		ft_dprintf(2, "color out of range\n");
		exit (1);
	}
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
			data->c_floor.r = set_color(ft_atoi(split_color[0]));
			data->c_floor.g = set_color(ft_atoi(split_color[1]));
			data->c_floor.b = set_color(ft_atoi(split_color[2]));
			ft_xfree(tmp);
			ft_free_null(split_color);
			data->c_floor.set = 1;
		}
		else
			ft_dprintf(2, "error\n2 F\n");
	}
	else if (!ft_strcmp_until(str, "C", ' '))
	{
		if (!data->c_sky.set)
		{
			tmp = del_space(ft_strdup(str + 1));
			split_color = ft_split(tmp, ',');
			data->c_sky.r = set_color(ft_atoi(split_color[0]));
			data->c_sky.g = set_color(ft_atoi(split_color[1]));
			data->c_sky.b = set_color(ft_atoi(split_color[2]));
			ft_xfree(tmp);
			ft_free_null(split_color);
			data->c_sky.set = 1;
		}
		else
			ft_dprintf(2, "error\n2 C\n");
	}
	return (data);
}

static t_data	*get_sprite(char *sprite, t_data *data)
{
	if (!ft_strcmp_until(sprite, "NO", ' '))
	{
		if (data->north.path)
			ft_dprintf(2, "error\n2 NO\n");
		data->north.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until(sprite, "SO", ' '))
	{
		if (data->south.path)
			ft_dprintf(2, "error\n2 SO\n");
		data->south.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until(sprite, "EA", ' '))
	{
		if (data->east.path)
			ft_dprintf(2, "error\n2 EA\n");
		data->east.path = del_space(ft_strdup(sprite + 2));
	}
	else if (!ft_strcmp_until(sprite, "WE", ' '))
	{
		if (data->west.path)
			ft_dprintf(2, "error\n2 WE\n");
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

t_data	*parse_map(char	**map, t_data *data)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		map[i] = del_space(map[i]);
		data = get_sprite(map[i], data);
		ft_printf("map[%d]	: %s\n", i, map[i]);
		i++;
	}
	return (data);
}