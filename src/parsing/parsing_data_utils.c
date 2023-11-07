#include "../../include/parsing.h"

char	*del_all_space(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		space;

	i = 0;
	j = 0;
	space = 0;;
	while (str && str[i])
	{
		if (str[i] == SP || str[i] == TAB)
			space++;
		i++;
	}
	res = ft_calloc((ft_strlen(str) - space) + 1, sizeof(char));
	i = 0;
	while (str && str[i])
	{
		while (str[i] == SP || str[i] == TAB)
			i++;
		res[j++] = str[i++];
	}
	return (free(str), res);
}
