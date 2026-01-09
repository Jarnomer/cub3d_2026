/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <types.h>

typedef struct s_map	t_map;

void	map_destroy(t_map *map);
bool	map_is_wall(t_map *map, t_i32 x, t_i32 y);

void	*safe_calloc(size_t size);
char	*safe_strjoin(char *s1, char *s2);
char	*safe_strdup(char *s1);
char	**safe_split(char *str, char c);

void	safe_mlx_init(t_game *game);
void	safe_image_to_window(mlx_t *mlx, t_mlxi *img, t_i32 x, t_i32 y);
t_mlxi	*safe_image(mlx_t *mlx, t_u32 w, t_u32 h);
t_mlxt	*safe_load_png(const char *path);

t_f32	ft_atof(const char *str);

void	free_str(char *str);
void	free_arr(char **arr);

#endif
