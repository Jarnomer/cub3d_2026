/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	safe_image_to_window(mlx_t *mlx, t_mimg *img, t_i32 x, t_i32 y)
{
	if (mlx_image_to_window(mlx, img, x, y) == -1)
		err_exit_mlx();
}

t_mimg	*safe_image(mlx_t *mlx, t_u32 w, t_u32 h)
{
	t_mimg	*img;

	img = mlx_new_image(mlx, w, h);
	if (!img)
		err_exit_mlx();
	return (img);
}

t_mtex	*safe_load_png(const char *path)
{
	t_mtex	*tex;

	tex = mlx_load_png(path);
	if (!tex)
		err_exit_mlx();
	return (tex);
}
