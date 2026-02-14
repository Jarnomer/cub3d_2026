/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_occlude.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	calc_slice(t_occlude *occ, t_game *game, t_i32 tex_h)
{
	t_i32	height;
	t_i32	pitch;
	t_i32	offset;

	if (occ->dist < EPSILON)
		occ->height = game->render.height;
	else
		occ->height = game->render.height / occ->dist;
	pitch = (t_i32)(game->camera.pitch * game->render.height);
	offset = camera_wall_offset(game, occ->dist);
	height = game->render.height / 2 - occ->height / 2;
	occ->top = height + pitch + offset;
	occ->step = (t_f32)tex_h / (t_f32)occ->height;
}

void	init_hit_ctx(t_occlude *occ, t_hit *hit, t_sheet *sheet)
{
	t_i32	tex_x;
	bool	flip;

	occ->dist = hit->dist;
	occ->entity = hit->entity;
	occ->tex.h = sheet->height;
	occ->tex.w = sheet->width;
	tex_x = (t_i32)(hit->wall_x * (t_f32)occ->tex.w);
	flip = (hit->axis == AXIS_X && hit->dir == WALL_EAST)
		|| (hit->axis == AXIS_Y && hit->dir == WALL_SOUTH);
	if (flip)
		tex_x = occ->tex.w - tex_x - 1;
	occ->tex.x = clampi(tex_x, 0, occ->tex.w - 1);
	occ->is_active = true;
}

void	occlude_store(t_game *game, t_hit *hit, t_i32 x)
{
	t_occlude	*occ;
	t_entity	*ent;
	t_sheet		*sheet;

	if (!game->render.occlude || x < 0 || x >= game->render.width)
		return ;
	ent = darray_get(&game->entities, hit->entity);
	if (!ent || !ent->is_active)
		return ;
	sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	occ = &game->render.occlude[x];
	init_hit_ctx(occ, hit, sheet);
	calc_slice(occ, game, sheet->height);
}

bool	occlude_pixel(t_game *game, t_i32 x, t_i32 y, t_f32 dist)
{
	t_occlude	*occ;
	t_entity	*ent;
	t_sheet		*sheet;
	t_u32		color;
	t_i32		frame;

	occ = &game->render.occlude[x];
	if (!occ->is_active || dist < occ->dist)
		return (false);
	ent = darray_get(&game->entities, occ->entity);
	if (!ent || !ent->is_active)
		return (false);
	sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return (false);
	occ->tex.y = (t_i32)((y - occ->top) * occ->step);
	occ->tex.y = clampi(occ->tex.y, 0, occ->tex.h - 1);
	frame = door_get_frame(ent, &game->assets);
	color = sheet_sample(sheet, frame, occ->tex.x, occ->tex.y);
	return (color_is_opaque(color));
}
