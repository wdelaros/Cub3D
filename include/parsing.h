/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:50:42 by wdelaros          #+#    #+#             */
/*   Updated: 2023/12/12 11:46:18 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//init_image.c
void	free_image(t_data *data);
mlx_t	*init_image(t_data *data);

//map.c
t_data	*parse_file(char **map, t_data *data);

//map_utils.c
int		count_char(char *str, char c);
char	ft_find_first_alphanum(char *str);
int		ft_strcmp_until_space(const char *s1, const char *s2);
char	*change_space(char *str, char **map, t_data *data);
char	**cpy_map(char **map, char **map_cpy);

//parsing.c
void	ft_parsing(char *file, t_data *data);
char	**ft_arrayjoin(char **src, char *s);
char	**ft_arrayzero(char **src, char *s);

//parsing_data.c
t_data	*get_sprite(char *sprite, char **map, t_data *data);

//parsing_data_utils.c
char	*del_all_space(char *str);

//parsing_utils.c
void	ft_purge_parsing(t_data	*data);
void	ft_exit_parsing(char *str_err, char **map, t_data *data);
int		check_color(char *str);
char	*del_space(char *str);
int		ft_strcmp_until(const char *s1, const char *s2, char c);

//valid_map.c
void	valid_map(char **map, char **map_free, t_data *data);

#endif