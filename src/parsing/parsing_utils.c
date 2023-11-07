#include "../../include/parsing.h"

void	ft_purge_parsing(t_data	*data)
{
	ft_xfree(data->north.path);
	ft_xfree(data->south.path);
	ft_xfree(data->east.path);
	ft_xfree(data->west.path);
	if (data->floor)
		ft_free_null(data->floor);
	if (data->sky)
		ft_free_null(data->sky);
	if (data->wall)
		ft_free_null(data->wall);
}

void	ft_exit_parsing(char *str_err, char **map, t_data *data)
{
	ft_dprintf(2, "Error\n%s\n", str_err);
	if (map)
		ft_free_null(map);
	ft_purge_parsing(data);
	exit (1);
}

int	check_color(char *str)
{
	if (!str || str[0] == -62 || ft_strlen(str) > 3 || !ft_isnumber(str))
		return (1);
	return (0);
}

char	*del_space(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str && (str[i] == SP || str[i] == TAB))
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
