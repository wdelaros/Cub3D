#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "structure.h"
# include <fcntl.h>

void	ft_parsing(char *file, t_data *data);
t_data	*parse_map(char	**map, t_data *data);
void	print_map(char **map);

#endif