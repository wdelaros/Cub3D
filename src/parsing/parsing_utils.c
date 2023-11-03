#include "../../include/parsing.h"

void	ft_purge_parsing(t_data	*data)
{
	ft_xfree(data->north.path);
	ft_xfree(data->south.path);
	ft_xfree(data->east.path);
	ft_xfree(data->west.path);
	ft_free_null(data->floor);
}

void	ft_exit_parsing(char *str_err, t_data *data)
{
	ft_dprintf(2, "%s\n", str_err);
	ft_purge_parsing(data);
	exit (1);
}

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
