/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	texture_load(t_tex *tex, const char *path)
{
	tex->mlx_tex = safe_load_png(path);
	tex->width = tex->mlx_tex->width;
	tex->height = tex->mlx_tex->height;
	tex->pixels = (t_u32 *)tex->mlx_tex->pixels;
}

void	texture_destroy(t_tex *tex)
{
	if (tex->mlx_tex)
		mlx_delete_texture(tex->mlx_tex);
	*tex = (t_tex){0};
}

t_u32	texture_sample(t_tex *tex, t_i32 x, t_i32 y)
{
	t_i32	idx;

	x = clampi(x, 0, tex->width - 1);
	y = clampi(y, 0, tex->height - 1);
	idx = y * tex->width + x;
	return (tex->pixels[idx]);
}

t_u32	texture_sample_wrap(t_tex *tex, t_f32 u, t_f32 v)
{
	t_i32	idx;
	t_i32	x;
	t_i32	y;

	x = (t_i32)(u * tex->width) % tex->width;
	y = (t_i32)(v * tex->height) % tex->height;
	if (x < 0)
		x += tex->width;
	if (y < 0)
		y += tex->height;
	idx = y * tex->width + x;
	return (tex->pixels[idx]);
}
