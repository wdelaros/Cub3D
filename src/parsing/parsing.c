/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:50:01 by wdelaros          #+#    #+#             */
/*   Updated: 2023/12/12 11:46:11 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	**ft_arrayjoin(char **src, char *s)
{
	char	**res;
	int		i;
	int		len;

	len = ft_strlen_double(src);
	res = ft_calloc(len + 2, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	if (!s)
		return (src);
	if (src)
	{
		while (src[i])
		{
			res[i] = ft_strdup(src[i]);
			i++;
		}
	}
	res[i] = ft_strdup(s);
	ft_free_null(src);
	return (res);
}

char	**ft_arrayzero(char **src, char *s)
{
	char	**res;
	int		i;
	int		len;

	len = ft_strlen_double(src);
	res = ft_calloc(len + 2, sizeof(char *));
	if (!res)
		return (NULL);
	i = 1;
	if (!s)
		return (src);
	if (src)
	{
		while (src[i - 1])
		{
			res[i] = ft_strdup(src[i - 1]);
			i++;
		}
	}
	res[0] = ft_strdup(s);
	ft_free_null(src);
	return (res);
}

static char	**ft_loadmap(char *path)
{
	char	**res;
	char	*added;
	int		ffs;

	ffs = open(path, O_RDONLY);
	if (ffs < 0)
		return (ft_dprintf(2, "Error\nMap does not exist\n"), NULL);
	if (path)
	{
		res = NULL;
		added = get_next_line(ffs);
		while (added)
		{
			res = ft_arrayjoin(res, added);
			added = ft_xfree(added);
			added = get_next_line(ffs);
		}
		added = ft_xfree(added);
		close(ffs);
		return (res);
	}
	return (NULL);
}

void	ft_parsing(char *file, t_data *data)
{
	char	**map;

	map = ft_loadmap(file);
	if (!map)
		ft_exit_parsing("Empty map", map, data);
	data = parse_file(map, data);
	ft_free_null(map);
}
