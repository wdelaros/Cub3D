#include "../../include/parsing.h"

static char	*get_file(char	*file, int i)
{
	int		fd;
	char	*str;
	char	*strdef;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_dprintf(2, "Error\nMap does not exist\n"), NULL);
	str = "x";
	while (str)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (i == 0)
			strdef = ft_strdup(str);
		else if (!ft_strcmp(str, "\n"))
			strdef = ft_ffstrjoin(strdef, ft_strjoin("\r", str));
		else
			strdef = ft_fstrjoin(strdef, str);
		free(str);
		i++;
	}
	close(fd);
	return (strdef);
}

static char	**get_map(char	*file)
{
	int		i;
	char	*str;
	char	**map;

	i = -1;
	str = get_file(file, 0);
	if (!str)
		return (NULL);
	map = ft_split(str, '\n');
	free(str);
	while (++i && map[i])
	{
		if (!ft_strncmp(map[i], "\r", 1))
		{
			free(map[i]);
			map[i] = ft_strdup("\n");
		}
	}
	return (map);
}

void	print_map(char **map)
{
	for (int i = 0; map[i]; i++)
	{
		if (!ft_strcmp(map[i], "\n"))
			ft_printf("%s", map[i]);
		else
			ft_printf("%s\n", map[i]);
	}
}

int	ft_parsing(char *file)
{
	char	**map;

	map = get_map(file);
	if (!map)
		return (1);
	print_map(map);
	map  =ft_free_null(map);
	return (0);
}
