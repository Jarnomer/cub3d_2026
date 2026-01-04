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
	ft_bzero(tex, sizeof(t_tex));
}

t_u32	texture_sample(t_tex *tex, t_i32 x, t_i32 y)
{
	t_i32	idx;

	x = clampi(x, 0, tex->width - 1);
	y = clampi(y, 0, tex->height - 1);
	idx = y * tex->width + x;
	return (tex->pixels[idx]);
}

t_color	texture_sample_color(t_tex *tex, t_i32 x, t_i32 y)
{
	t_u32	pixel;
	t_color	c;

	pixel = texture_sample(tex, x, y);
	c.r = (pixel >> 0) & 0xFF;
	c.g = (pixel >> 8) & 0xFF;
	c.b = (pixel >> 16) & 0xFF;
	c.a = (pixel >> 24) & 0xFF;
	return (c);
}
