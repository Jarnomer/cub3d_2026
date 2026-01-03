/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	safe_image_to_window(mlx_t *mlx, mlx_image_t *img, t_i32 x, t_i32 y)
{
	if (mlx_image_to_window(mlx, img, x, y) == -1)
		err_exit_mlx();
}

mlx_image_t	*safe_image(mlx_t *mlx, t_u32 w, t_u32 h)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, w, h);
	if (!img)
		err_exit_mlx();
	return (img);
}

mlx_texture_t	*safe_load_png(const char *path)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(path);
	if (!tex)
		err_exit_mlx();
	return (tex);
}
