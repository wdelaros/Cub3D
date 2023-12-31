/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:49:50 by wdelaros          #+#    #+#             */
/*   Updated: 2023/12/08 16:49:51 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	|| !ft_strcmp(str, "\n") || !ft_strcmp(str, "\0"))
		return (1);
	return (0);
}

static int	check_char_map(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		j = 0;
		if (!ft_strcmp_until(str[i], "\0", GS))
			return (-1);
		while (str && str[i][j])
		{
			if (str[i][j] == GS || str[i][j] == '1' || str[i][j] == '0')
				;
			else if (str && str[i][j] && (str[i][j] == 'N' || str[i][j] == 'S' \
			|| str[i][j] == 'E' || str[i][j] == 'W'))
				count++;
			else
				return (-1);
			j++;
		}
		i++;
	}
	return (count);
}

static t_data	*parse_map(t_data *data, char **map, int i)
{
	data->wall = cpy_map(NULL, map + i);
	i = 0;
	while (data->wall[i])
	{
		if (data->wall[i][ft_strlen(data->wall[i]) - 1] == '\n')
			data->wall[i][ft_strlen(data->wall[i]) - 1] = '\0';
		data->wall[i] = change_space(data->wall[i], map, data);
		i++;
	}
	if (check_char_map(data->wall) == -1)
		ft_exit_parsing("Invalid data in map", map, data);
	else if (check_char_map(data->wall) != 1)
		ft_exit_parsing("Invalid number of player", map, data);
	valid_map(data->wall, map, data);
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
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = '\0';
		map[i] = del_space(map[i]);
		if (is_correct_data(map[i]))
			data = get_sprite(map[i], map, data);
		else
			ft_exit_parsing("Wrong identifier", map, data);
		i++;
	}
	if (!data->c_floor.set || !data->c_sky.set || !data->north.path \
		|| !data->south.path || !data->east.path || !data->west.path)
		ft_exit_parsing("Missing information", map, data);
	else
		data = parse_map(data, map, i);
	return (data);
}
