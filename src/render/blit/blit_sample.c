/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_sample.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	blit_calc_size(t_blit *blit, t_i32 src_w, t_i32 src_h, t_f32 scale)
{
	blit->src_size.x = src_w;
	blit->src_size.y = src_h;
	blit->scale = scale;
	blit->inv_scale = 1.0f / scale;
	blit->size.x = (t_i32)(src_w * scale);
	blit->size.y = (t_i32)(src_h * scale);
}

void	blit_from_tex(t_blit *blit, t_tex *tex, t_f32 scale)
{
	*blit = (t_blit){0};
	if (!tex || !tex->pixels)
		return ;
	blit->tex = tex;
	blit_calc_size(blit, tex->width, tex->height, scale);
}

void	blit_from_sheet(t_blit *blit, t_sheet *sheet, t_i32 frame, t_f32 scale)
{
	*blit = (t_blit){0};
	if (!sheet || !sheet->tex.pixels)
		return ;
	blit->sheet = sheet;
	blit->frame = frame;
	blit_calc_size(blit, sheet->width, sheet->height, scale);
}

static t_vec2i	blit_src_coord(t_blit *blit, t_i32 x, t_i32 y)
{
	t_vec2i	src;

	src.x = (t_i32)((x - blit->start.x + blit->offset.x) * blit->inv_scale);
	src.y = (t_i32)((y - blit->start.y + blit->offset.y) * blit->inv_scale);
	src.x = clampi(src.x, 0, blit->src_size.x - 1);
	src.y = clampi(src.y, 0, blit->src_size.y - 1);
	return (src);
}

t_u32	blit_sample(t_blit *blit, t_i32 x, t_i32 y)
{
	t_vec2i	src;

	src = blit_src_coord(blit, x, y);
	if (blit->sheet)
		return (sheet_sample(blit->sheet, blit->frame, src.x, src.y));
	if (blit->tex)
		return (texture_sample(blit->tex, src.x, src.y));
	return (0);
}
