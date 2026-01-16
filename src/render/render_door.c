/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_door_column(t_game *game, t_slice *slice, t_sheet *sheet,
	t_i32 x)
{
	t_u32	color;
	t_u32	fog;
	t_i32	tex_y;
	t_i32	y;

	slice_calc_tex_step(slice, sheet->height);
	fog = lookup_fog(&game->lookup, slice->dist);
	y = slice->start;
	while (y <= slice->end)
	{
		tex_y = clampi((t_i32)slice->tex_y, 0, sheet->height - 1);
		color = sheet_sample(sheet, slice->frame, slice->tex_x, tex_y);
		if (color_is_opaque(color))
			render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		slice->tex_y += slice->step;
		y++;
	}
}

void	render_door_column(t_game *game, t_hit *hit, t_i32 x)
{
	t_entity	*ent;
	t_sheet		*sheet;
	t_slice		slice;

	if (hit->entity < 0)
		return ;
	ent = darray_get(&game->entities, hit->entity);
	if (!ent || !ent->is_active)
		return ;
	sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	slice = slice_from_hit(hit, game->render.height, sheet->width);
	slice.frame = door_get_frame(ent, &game->assets);
	slice_apply_height(&slice, game);
	slice_apply_pitch(&slice, game);
	draw_door_column(game, &slice, sheet, x);
}
