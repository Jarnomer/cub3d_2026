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

/*
** Door-aware occlusion for sprite rendering
**
** Problem: When door opens, sprites behind it should gradually appear
** as the door texture becomes transparent, not instantly when state changes.
**
**     Door animation frames:
**     Frame 0 (closed)    Frame 4 (half)     Frame 8 (open)
**     +------------+      +------------+      +------------+
**     |############|      |####    ####|      |            |
**     |############|  ->  |####    ####|  ->  |            |
**     |############|      |####    ####|      |            |
**     +------------+      +------------+      +------------+
**          ^                   ^                   ^
**     sprite hidden      sprite partial      sprite visible
**
** Solution: Store door hit info per column, then when rendering sprites,
** sample the door texture to check if that specific pixel is occluded.
*/

/*
** Stores door occlusion data for a screen column
**
** Called during wall rendering when a non-blocking door is encountered.
** The data is used later by sprite rendering to check per-pixel occlusion.
*/
void	occlude_store_door(t_game *game, t_hit *door_hit, t_i32 x)
{
	t_occlude	*occ;

	if (!game->render.occlude || x < 0 || x >= game->render.width)
		return ;
	occ = &game->render.occlude[x];
	occ->has_door = true;
	occ->door_dist = door_hit->dist;
	occ->entity_idx = door_hit->entity;
	occ->wall_x = door_hit->wall_x;
	occ->axis = door_hit->axis;
	occ->dir = door_hit->dir;
}

/*
** Clears occlusion data for a screen column
**
** Called at start of wall rendering or when no door in column
*/
void	occlude_clear_column(t_game *game, t_i32 x)
{
	if (!game->render.occlude || x < 0 || x >= game->render.width)
		return ;
	game->render.occlude[x] = (t_occlude){0};
}

/*
** Calculates door texture Y coordinate for a given screen Y
**
** Uses same projection math as door rendering to find where
** on the door texture this screen pixel maps to.
*/
static t_i32	calc_door_tex_y(t_game *game, t_occlude *occ, t_i32 y, t_i32 th)
{
	t_i32	wall_h;
	t_i32	wall_top;
	t_i32	pitch_off;
	t_i32	tex_y;

	wall_h = (t_i32)(game->render.height / occ->door_dist);
	pitch_off = (t_i32)(game->camera.pitch * game->render.height);
	wall_top = game->render.height / 2 - wall_h / 2 + pitch_off;
	tex_y = (y - wall_top) * th / wall_h;
	return (clampi(tex_y, 0, th - 1));
}

/*
** Calculates door texture X coordinate from stored wall_x
*/
static t_i32	calc_door_tex_x(t_occlude *occ, t_i32 tex_w)
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

/*
** Checks if a sprite pixel is occluded by the door at this column
**
** Returns true if:
**   1. There's a door in this column
**   2. The sprite is behind the door
**   3. The door pixel at this location is opaque
**
** This allows sprites to "show through" transparent parts of the door
** texture as the door opens.
*/
bool	occlude_check_door(t_game *game, t_i32 x, t_i32 y, t_f32 sprite_dist)
{
	t_occlude	*occ;
	t_entity	*ent;
	t_sheet		*sheet;
	t_i32		frame;
	t_u32		color;

	if (!game->render.occlude)
		return (false);
	occ = &game->render.occlude[x];
	if (!occ->has_door)
		return (false);
	if (sprite_dist < occ->door_dist)
		return (false);
	ent = darray_get(&game->entities, occ->entity_idx);
	if (!ent || !ent->active)
		return (false);
	sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return (false);
	frame = door_get_frame(ent, &game->assets);
	color = sheet_sample(sheet, frame,
			calc_door_tex_x(occ, sheet->width),
			calc_door_tex_y(game, occ, y, sheet->height));
	return (color_a(color) > ALPHA_THRESHOLD);
}
