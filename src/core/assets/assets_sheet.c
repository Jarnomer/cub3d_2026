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
	sheet->frames = cols * rows;
	sheet->width = sheet->tex.width / cols;
	sheet->height = sheet->tex.height / rows;
}

void	sheet_destroy(t_sheet *sheet)
{
	texture_destroy(&sheet->tex);
	*sheet = (t_sheet){0};
}

t_u32	sheet_sample(t_sheet *sheet, t_i32 frame, t_i32 u, t_i32 v)
{
	t_vec2i	tex;
	t_i32	col;
	t_i32	row;

	frame = clampi(frame, 0, sheet->frames - 1);
	col = frame % sheet->cols;
	row = frame / sheet->cols;
	u = clampi(u, 0, sheet->width - 1);
	v = clampi(v, 0, sheet->height - 1);
	tex.x = col * sheet->width + u;
	tex.y = row * sheet->height + v;
	return (texture_sample(&sheet->tex, tex.x, tex.y));
}
