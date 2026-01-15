/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_vec2i	blit_src_coord(t_blit *blit, t_i32 x, t_i32 y)
{
	t_vec2i	src;

	src.x = (t_i32)((x - blit->bounds.x + blit->offset.x) * blit->inverse);
	src.y = (t_i32)((y - blit->bounds.y + blit->offset.y) * blit->inverse);
	src.x = clampi(src.x, 0, blit->source.x - 1);
	src.y = clampi(src.y, 0, blit->source.y - 1);
	return (src);
}

static t_u32	blit_sample(t_blit *blit, t_i32 x, t_i32 y)
{
	t_vec2i	src;

	src = blit_src_coord(blit, x, y);
	if (blit->sheet)
		return (sheet_sample(blit->sheet, blit->frame, src.x, src.y));
	if (blit->tex)
		return (texture_sample(blit->tex, src.x, src.y));
	return (0);
}

static void	blit_row(t_blit *blit, t_mlxi *img, t_i32 y)
{
	t_pixels	pixels;
	t_u32		color;
	t_i32		x;

	pixels = (t_pixels)img->pixels;
	x = blit->bounds.x;
	while (x < blit->bounds.x + blit->bounds.w)
	{
		color = blit_sample(blit, x, y);
		if ((color >> 24) >= ALPHA_THRESHOLD)
			pixels[y * img->width + x] = color;
		x++;
	}
}

void	blit_render(t_blit *blit, t_mlxi *img)
{
	t_i32	height;
	t_i32	y;

	if (!img || (!blit->tex && !blit->sheet))
		return ;
	if (!rect_is_valid(blit->bounds))
		return ;
	height = blit->bounds.y + blit->bounds.h;
	y = blit->bounds.y;
	while (y < height)
	{
		blit_row(blit, img, y);
		y++;
	}
}
