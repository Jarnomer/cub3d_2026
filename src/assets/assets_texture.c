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
	tex->texture = safe_load_png(path);
	tex->width = tex->texture->width;
	tex->height = tex->texture->height;
	tex->pixels = (t_pixels)tex->texture->pixels;
}

void	texture_destroy(t_tex *tex)
{
	if (tex->texture)
		mlx_delete_texture(tex->texture);
	*tex = (t_tex){0};
}

t_u32	texture_sample(t_tex *tex, t_i32 u, t_i32 v)
{
	t_i32	idx;

	u = clampi(u, 0, tex->width - 1);
	v = clampi(v, 0, tex->height - 1);
	idx = v * tex->width + u;
	return (tex->pixels[idx]);
}

t_u32	texture_sample_wrap(t_tex *tex, t_f32 u, t_f32 v)
{
	t_i32	idx;

	u = (t_i32)(u * tex->width) % tex->width;
	v = (t_i32)(v * tex->height) % tex->height;
	if (u < 0)
		u += tex->width;
	if (v < 0)
		v += tex->height;
	idx = v * tex->width + u;
	return (tex->pixels[idx]);
}
