#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "structure.h"
# include <fcntl.h>

# define TAB 9
# define FS 28
# define GS 29
# define RS 30
# define US 31
# define SP 32

//parsing.c
void	ft_parsing(char *file, t_data *data);
void	print_map(char **map);

//parsing_data.c
t_data	*get_sprite(char *sprite, char **map, t_data *data);

//parsing_data_utils.c
char	*del_all_space(char *str);

//parsing_utils.c
void	ft_purge_parsing(t_data	*data);
void	ft_exit_parsing(char *str_err, char **map, t_data *data);
int		ft_strcmp_until(const char *s1, const char *s2, char c);
char	*del_space(char *str);

//map.c
t_data	*parse_file(char **map, t_data *data);

//map_utils
int		check_color(char *str);
int		count_char(char *str, char c);
int		ft_strcmp_until_space(const char *s1, const char *s2);
char	ft_find_first_alphanum(char *str);

#endif