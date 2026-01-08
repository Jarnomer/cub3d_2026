/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sample.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_u32	sample_texture_uv(t_tex *tex, t_f32 u, t_f32 v)
{
	t_i32	x;
	t_i32	y;

	x = (t_i32)(u * tex->width);
	y = (t_i32)(v * tex->height);
	x = clampi(x, 0, tex->width - 1);
	y = clampi(y, 0, tex->height - 1);
	return (tex->pixels[y * tex->width + x]);
}

t_u32	sample_texture_wrap(t_tex *tex, t_f32 u, t_f32 v)
{
	t_i32	x;
	t_i32	y;

	x = (t_i32)(u * tex->width) % tex->width;
	y = (t_i32)(v * tex->height) % tex->height;
	if (x < 0)
		x += tex->width;
	if (y < 0)
		y += tex->height;
	return (tex->pixels[y * tex->width + x]);
}

t_u32	sample_sheet_frame(t_sheet *sheet, t_i32 frame, t_i32 x, t_i32 y)
{
	t_i32	col;
	t_i32	row;
	t_i32	sheet_x;
	t_i32	sheet_y;

	frame = clampi(frame, 0, sheet->count - 1);
	col = frame % sheet->cols;
	row = frame / sheet->cols;
	x = clampi(x, 0, sheet->width - 1);
	y = clampi(y, 0, sheet->height - 1);
	sheet_x = col * sheet->width + x;
	sheet_y = row * sheet->height + y;
	return (texture_sample(&sheet->tex, sheet_x, sheet_y));
}

bool	sample_is_transparent(t_u32 color)
{
	return (color_a(color) < ALPHA_THRESHOLD);
}

bool	sample_is_opaque(t_u32 color)
{
	return (color_a(color) >= ALPHA_THRESHOLD);
}
