/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_occlude.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	occlude_store(t_game *game, t_hit *hit, t_i32 x)
{
	t_occlude	*occ;

	if (!game->render.occlude || x < 0 || x >= game->render.width)
		return ;
	occ = &game->render.occlude[x];
	occ->has_door = true;
	occ->door_dist = hit->dist;
	occ->entity_idx = hit->entity;
	occ->wall_x = hit->wall_x;
	occ->axis = hit->axis;
	occ->dir = hit->dir;
}

void	occlude_clear(t_game *game, t_i32 x)
{
	if (!game->render.occlude || x < 0 || x >= game->render.width)
		return ;
	game->render.occlude[x] = (t_occlude){0};
}

static t_i32	calc_tex_x(t_occlude *occ, t_i32 tex_w)
{
	t_i32	tex_x;
	bool	flip;

	tex_x = (t_i32)(occ->wall_x * (t_f32)tex_w);
	flip = (occ->axis == AXIS_X && occ->dir == WALL_EAST)
		|| (occ->axis == AXIS_Y && occ->dir == WALL_SOUTH);
	if (flip)
		tex_x = tex_w - tex_x - 1;
	return (clampi(tex_x, 0, tex_w - 1));
}

static t_i32	calc_tex_y(t_game *game, t_occlude *occ, t_i32 y, t_i32 tex_h)
{
	t_i32	wall_h;
	t_i32	wall_top;
	t_i32	pitch_off;

	wall_h = (t_i32)(game->render.height / occ->door_dist);
	pitch_off = (t_i32)(game->camera.pitch * game->render.height);
	wall_top = game->render.height / 2 - wall_h / 2 + pitch_off;
	return (clampi((y - wall_top) * tex_h / wall_h, 0, tex_h - 1));
}

bool	occlude_pixel(t_game *game, t_i32 x, t_i32 y, t_f32 sprite_dist)
{
	t_occlude	*occ;
	t_entity	*ent;
	t_sheet		*sheet;
	t_u32		color;

	if (!game->render.occlude || x < 0 || x >= game->render.width)
		return (false);
	occ = &game->render.occlude[x];
	if (!occ->has_door || sprite_dist < occ->door_dist)
		return (false);
	ent = darray_get(&game->entities, occ->entity_idx);
	if (!ent || !ent->active)
		return (false);
	sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return (false);
	color = sheet_sample(sheet, door_get_frame(ent, &game->assets),
			calc_tex_x(occ, sheet->width),
			calc_tex_y(game, occ, y, sheet->height));
	return (color_a(color) >= ALPHA_THRESHOLD);
}
