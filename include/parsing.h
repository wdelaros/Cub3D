#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "structure.h"
# include <fcntl.h>

//parsing.c
void	ft_parsing(char *file, t_data *data);
void	print_map(char **map);

//parsing_utils.c
void	ft_purge_parsing(t_data	*data);
void	ft_exit_parsing(char *str_err, t_data *data);
char	*del_space(char *str);
int	ft_strcmp_until(const char *s1, const char *s2, char c);

//map.c
t_data	*parse_map(t_data *data);

#endif