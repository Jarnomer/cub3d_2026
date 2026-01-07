/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sheet_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_i32	calc_sheet_tex_y(t_proj *proj, t_i32 screen_y, t_i32 frame_h)
{
	t_i32	sprite_y;
	t_i32	tex_y;

	sprite_y = screen_y - (proj->screen.y - proj->size.y / 2);
	tex_y = sprite_y * frame_h / proj->size.y;
	return (clampi(tex_y, 0, frame_h - 1));
}

static t_i32	calc_sheet_tex_x(t_proj *proj, t_i32 screen_x, t_i32 frame_w)
{
	t_i32	sprite_x;
	t_i32	tex_x;

	sprite_x = screen_x - (proj->screen.x - proj->size.x / 2);
	tex_x = sprite_x * frame_w / proj->size.x;
	return (clampi(tex_x, 0, frame_w - 1));
}

void	render_sheet_column(t_game *game, t_proj *proj, t_i32 x)
{
	t_sheet	*sheet;
	t_i32	tex_x;
	t_i32	y;
	t_u32	color;

	sheet = assets_get_sheet(&game->assets, proj->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	tex_x = calc_sheet_tex_x(proj, x, sheet->width);
	y = proj->start.y;
	while (y < proj->end.y)
	{
		color = sheet_sample(sheet, proj->frame,
				tex_x, calc_sheet_tex_y(proj, y, sheet->height));
		if ((color >> 24) > 128)
		{
			color = fog_blend(color, fog_factor(proj->dist));
			render_pixel(game->render.frame, x, y, color);
		}
		y++;
	}
}
