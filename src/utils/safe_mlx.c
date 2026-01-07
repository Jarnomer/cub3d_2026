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

void	safe_image_to_window(mlx_t *mlx, t_mlxi *img, t_i32 x, t_i32 y)
{
	if (mlx_image_to_window(mlx, img, x, y) == -1)
		err_exit_mlx();
}

t_mlxi	*safe_image(mlx_t *mlx, t_u32 w, t_u32 h)
{
	t_mlxi	*img;

	img = mlx_new_image(mlx, w, h);
	if (!img)
		err_exit_mlx();
	return (img);
}

t_mlxt	*safe_load_png(const char *path)
{
	t_mlxt	*tex;
	int		fd;

	fd = parse_file_open(path, ".png");
	if (fd < 0)
		err_exit_errno(path);
	tex = mlx_load_png(path);
	if (!tex)
		err_exit_mlx();
	close(fd);
	return (tex);
}
