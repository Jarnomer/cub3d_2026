/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_sheet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	sheet_load(t_sheet *sheet, const char *path, t_i32 cols, t_i32 rows)
{
	texture_load(&sheet->tex, path);
	sheet->cols = cols;
	sheet->rows = rows;
	sheet->count = cols * rows;
	sheet->width = sheet->tex.width / cols;
	sheet->height = sheet->tex.height / rows;
}

void	sheet_destroy(t_sheet *sheet)
{
	texture_destroy(&sheet->tex);
	*sheet = (t_sheet){0};
}

static t_vec2i	sheet_frame_offset(t_sheet *sheet, t_i32 frame)
{
	t_vec2i	offset;
	t_i32	col;
	t_i32	row;

	frame = clampi(frame, 0, sheet->count - 1);
	col = frame % sheet->cols;
	row = frame / sheet->cols;
	offset.x = col * sheet->width;
	offset.y = row * sheet->height;
	return (offset);
}

t_u32	sheet_sample(t_sheet *sheet, t_i32 frame, t_i32 x, t_i32 y)
{
	t_vec2i	offset;
	t_i32	sheet_x;
	t_i32	sheet_y;

	offset = sheet_frame_offset(sheet, frame);
	x = clampi(x, 0, sheet->width - 1);
	y = clampi(y, 0, sheet->height - 1);
	sheet_x = offset.x + x;
	sheet_y = offset.y + y;
	return (texture_sample(&sheet->tex, sheet_x, sheet_y));
}
