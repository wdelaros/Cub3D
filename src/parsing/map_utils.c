#include "../../include/parsing.h"

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

char	ft_find_first_alphanum(char *str)
{
	int	i;

	i = 0;
	while (str && (str[i] == SP || str[i] == TAB))
		i++;
	return (str[i]);
}

int	ft_strcmp_until_space(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] == s2[i] && ((s1[i + 1] != SP \
	&& s1[i + 1] != TAB) || s2[i + 1]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
