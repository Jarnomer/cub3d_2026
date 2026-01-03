/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

# include <MLX42.h>
# include <libft.h>

# include <game.h>
# include <config.h>
# include <parse.h>
# include <pool.h>
# include <calc.h>
# include <error.h>
# include <types.h>
# include <vector.h>

void			*safe_calloc(size_t size);
char			*safe_strjoin(char *s1, char *s2);
char			*safe_strdup(char *s1);
char			**safe_split(char *str, char c);

void			safe_image_to_window(mlx_t *mlx,
					mlx_image_t *img, t_i32 x, t_i32 y);
mlx_image_t		*safe_image(mlx_t *mlx, t_u32 w, t_u32 h);
mlx_texture_t	*safe_load_png(const char *path);

#endif
