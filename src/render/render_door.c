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

static void	draw_door_pixel(t_game *game, t_i32 x, t_i32 y, t_u32 color)
{
	t_u32	pixel;
	t_u8	alpha;
	t_mlxi	*frame;

	frame = game->render.frame;
	alpha = color_a(color);
	if (alpha < ALPHA_THRESHOLD)
		return ;
	if (alpha >= ALPHA_OPAQUE)
	{
		render_pixel(frame, x, y, color);
		return ;
	}
	pixel = ((t_u32 *)frame->pixels)[y * frame->width + x];
	render_pixel(frame, x, y, color_blend(color, pixel, alpha));
}

static void	draw_door_column(t_game *game, t_i32 x, t_slice *s, t_door *door)
{
	t_i32	y;
	t_i32	tex_y;
	t_u32	color;
	t_u8	fog;

	slice_calc_tex_step(s, door->sheet->height);
	fog = lookup_fog(&game->lookup, s->dist);
	y = s->start;
	while (y <= s->end)
	{
		tex_y = clampi((t_i32)s->tex_y, 0, door->sheet->height - 1);
		color = sheet_sample(door->sheet, door->frame, s->tex_x, tex_y);
		color = fog_apply(color, fog);
		draw_door_pixel(game, x, y, color);
		s->tex_y += s->step;
		y++;
	}
}

static bool	init_door_door(t_game *game, t_hit *hit, t_door *door)
{
	t_entity	*ent;

	if (hit->entity < 0)
		return (false);
	ent = darray_get(&game->entities, hit->entity);
	if (!ent || !ent->active)
		return (false);
	door->sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!door->sheet || !door->sheet->tex.pixels)
		return (false);
	door->frame = door_get_frame(ent, &game->assets);
	door->is_blocking = door_is_blocking(ent);
	return (true);
}

void	render_door_column(t_game *game, t_hit *hit, t_i32 x)
{
	t_slice	slice;
	t_door	door;

	if (!init_door_door(game, hit, &door))
		return ;
	slice = slice_from_hit(hit, game->render.height, door.sheet->width);
	slice_apply_pitch(&slice, &game->camera, game->render.height);
	if (door.is_blocking)
		zbuf_write(&game->render, x, hit->dist);
	draw_door_column(game, x, &slice, &door);
}
