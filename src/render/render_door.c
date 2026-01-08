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

/*
** Draws a pixel with alpha blending for door transparency
**
** Door textures may have semi-transparent pixels for smooth edges
** or opening animations. This function handles three cases:
**
**   alpha < ALPHA_THRESHOLD  -> fully transparent, skip
**   alpha >= ALPHA_OPAQUE    -> fully opaque, overwrite
**   otherwise                -> blend with existing pixel
*/

static void	draw_door_pixel(t_game *game, t_i32 x, t_i32 y, t_u32 color)
{
	t_u32	existing;
	t_u8	alpha;

	alpha = color_a(color);
	if (alpha < ALPHA_THRESHOLD)
		return ;
	if (alpha >= ALPHA_OPAQUE)
	{
		render_pixel(game->render.frame, x, y, color);
		return ;
	}
	existing = ((t_u32 *)game->render.frame->pixels)
	[y * game->render.frame->width + x];
	render_pixel(game->render.frame, x, y, color_blend(color, existing, alpha));
}

/*
** Draws a single vertical strip of door texture
**
** Similar to wall rendering but uses sprite sheet sampling
** and supports alpha blending for transparent door pixels
*/
static void	draw_door_column(t_game *game, t_i32 x, t_slice *s, t_door *ctx)
{
	t_i32	y;
	t_i32	tex_y;
	t_u32	color;
	t_u8	fog;

	fog = lookup_fog(&game->lookup, s->dist);
	slice_calc_texstep(s, ctx->sheet->height);
	y = s->start;
	while (y <= s->end)
	{
		tex_y = clampi((t_i32)s->tex_pos, 0, ctx->sheet->height - 1);
		color = sheet_sample(ctx->sheet, ctx->frame, s->tex_x, tex_y);
		color = fog_apply(color, fog);
		draw_door_pixel(game, x, y, color);
		s->tex_pos += s->tex_step;
		y++;
	}
}

/*
** Prepares door rendering context from entity data
**
** Returns false if door entity is invalid or missing required assets
*/

static bool	door_prepare_ctx(t_game *game, t_hit *hit, t_door *ctx)
{
	t_entity	*ent;

	if (hit->entity < 0)
		return (false);
	ent = darray_get(&game->entities, hit->entity);
	if (!ent || !ent->active)
		return (false);
	ctx->sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!ctx->sheet || !ctx->sheet->tex.pixels)
		return (false);
	ctx->frame = door_get_frame(ent, &game->assets);
	ctx->is_blocking = door_is_blocking(ent);
	return (true);
}

/*
** Renders a door column as wall-aligned sprite
** Multithreaded function call with column width restriction
**
** Z-BUFFER RULES (critical for correct sprite occlusion):
**
**   BLOCKING door (closed):
**     - Acts as solid wall
**     - WRITES to z-buffer (sprites behind door are hidden)
**
**   NON-BLOCKING door (open/opening):
**     - Rendered as overlay on top of wall behind
**     - Does NOT write z-buffer
**     - Wall behind already set correct occlusion distance
**     - Sprites between camera and wall render correctly
**
**   Visual example (top-down view):
**
**     Camera ---> [Barrel] ---> |Door| ---> |Wall|
**
**   When door is CLOSED:
**     z_buffer = door_dist
**     Barrel (dist < door_dist) -> RENDERS (in front of door)
**
**   When door is OPEN:
**     z_buffer = wall_dist (set by wall render, door skipped)
**     Barrel (dist < wall_dist) -> RENDERS (in front of wall)
**
**   BUG if door always writes z-buffer when open:
**     z_buffer = door_dist (incorrectly set)
**     Barrel (dist > door_dist but < wall_dist) -> CULLED (wrong!)
*/

void	render_door_column(t_game *game, t_hit *hit, t_i32 x)
{
	t_door	ctx;
	t_slice	slice;

	if (!door_prepare_ctx(game, hit, &ctx))
		return ;
	slice = slice_from_hit(hit, game->render.height, ctx.sheet->width);
	slice_apply_pitch(&slice, &game->camera, game->render.height);
	if (ctx.is_blocking)
		game->render.z_buffer[x] = hit->dist;
	draw_door_column(game, x, &slice, &ctx);
}
