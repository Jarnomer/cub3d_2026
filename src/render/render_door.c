/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_door_column(t_game *game, t_i32 x, t_slice *s, t_door *door)
{
	t_u32	color;
	t_u32	fog;
	t_i32	tex_y;
	t_i32	y;

	slice_calc_tex_step(s, door->sheet->height);
	fog = lookup_fog(&game->lookup, s->dist);
	y = s->start;
	while (y <= s->end)
	{
		tex_y = clampi((t_i32)s->tex_y, 0, door->sheet->height - 1);
		color = sheet_sample(door->sheet, door->frame, s->tex_x, tex_y);
		if (color_is_opaque(color))
			render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		s->tex_y += s->step;
		y++;
	}
}

static bool	init_door_ctx(t_game *game, t_hit *hit, t_door *door)
{
	t_entity	*ent;

	if (hit->entity < 0)
		return (false);
	ent = darray_get(&game->entities, hit->entity);
	if (!ent || !ent->is_active)
		return (false);
	door->sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!door->sheet || !door->sheet->tex.pixels)
		return (false);
	door->frame = door_get_frame(ent, &game->assets);
	return (true);
}

void	render_door_column(t_game *game, t_hit *hit, t_i32 x)
{
	t_slice	slice;
	t_door	door;

	if (!init_door_ctx(game, hit, &door))
		return ;
	slice = slice_from_hit(hit, game->render.height, door.sheet->width);
	slice_apply_pitch(&slice, &game->camera, game->render.height);
	draw_door_column(game, x, &slice, &door);
}
