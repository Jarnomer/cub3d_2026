/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_sheet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
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
