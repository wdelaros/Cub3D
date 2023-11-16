#include "../../include/parsing.h"

static int	check_arround_identifier(char **map, int i, int j)
{
	int	len;

	len = ft_strlen_double(map);
	if (i == 0 || j == 0 || i == (int)ft_strlen_double(map) - 1 \
	|| j == (int)ft_strlen(map[i]) - 1)
		return (1);
	if (i > 0 && j < (int)ft_strlen(map[i - 1]) && (map[i - 1][j] != '0' \
	&& map[i - 1][j] != '1' && map[i - 1][j] != 'N' && map[i - 1][j] != 'S' \
	&& map[i - 1][j] != 'E' && map[i - 1][j] != 'W'))
		return (1);
	if (i <= len - 1 && j < (int)ft_strlen(map[i + 1]) && (map[i - 1][j] != '0' \
	&& map[i - 1][j] != '1' && map[i - 1][j] != 'N' && map[i - 1][j] != 'S' \
	&& map[i - 1][j] != 'E' && map[i - 1][j] != 'W'))
		return (1);
	if (j > 0 && (map[i - 1][j] != '0' && map[i - 1][j] != '1' \
	&& map[i - 1][j] != 'N' && map[i - 1][j] != 'S' && map[i - 1][j] != 'E' \
	&& map[i - 1][j] != 'W'))
		return (1);
	if (j <= (int)ft_strlen(map[i]) && (map[i - 1][j] != '0' \
	&& map[i - 1][j] != '1' && map[i - 1][j] != 'N' && map[i - 1][j] != 'S' \
	&& map[i - 1][j] != 'E' && map[i - 1][j] != 'W'))
		return (1);
	return (0);
}

static int	check_arround_space(char **map, int i, int j)
{
	int	len;

	len = ft_strlen_double(map);
	if (i > 0 && j < (int)ft_strlen(map[i - 1]) && (map[i - 1][j] != GS \
	&& map[i - 1][j] != '1'))
		return (1);
	if (i <= len - 1 && j < (int)ft_strlen(map[i + 1]) && (map[i + 1][j] != GS \
	&& map[i + 1][j] != '1'))
		return (1);
	if (j > 0 && (map[i][j - 1] != GS && map[i][j - 1] != '1'))
		return (1);
	if (j <= (int)ft_strlen(map[i]) && (map[i][j + 1] != GS \
	&& map[i][j + 1] != '1'))
		return (1);
	return (0);
}

void	valid_map(char **map, char **map_free, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' \
			|| map[i][j] == 'E' || map[i][j] == 'W') \
			&& check_arround_identifier(map, i, j))
				ft_exit_parsing("identifier error", map_free, data);
			if (map[i][j] == GS && check_arround_space(map, i, j))
				ft_exit_parsing("space error", map_free, data);
			j++;
		}
		i++;
	}
}
