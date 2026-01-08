/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

/*
** Samples texture at world position with wrapping
**
** World coordinates are fractional, so we:
**   1. Scale by texture dimensions
**   2. Modulo to wrap within texture bounds
**   3. Handle negative coordinates (behind camera)
*/

static t_u32	sample_floor_tex(t_tex *tex, t_vec2 world_pos)
{
	t_i32	tex_x;
	t_i32	tex_y;

	tex_x = (t_i32)(world_pos.x * tex->width) % tex->width;
	tex_y = (t_i32)(world_pos.y * tex->height) % tex->height;
	if (tex_x < 0)
		tex_x += tex->width;
	if (tex_y < 0)
		tex_y += tex->height;
	return (texture_sample(tex, tex_x, tex_y));
}

/*
** Draws a horizontal row of floor or ceiling pixels
**
** Steps through world coordinates from left to right edge,
** sampling texture at each position
**
** Early exit if FOG_FULL (completely fogged, no texture visible)
*/

static void	draw_floor_row(t_game *game, t_floor *f, t_tex *tex, t_i32 y)
{
	t_i32	x;
	t_u32	color;
	t_u8	fog;

	fog = lookup_fog(&game->lookup, f->dist);
	if (fog == FOG_FULL)
	{
		fog_fill_row(game, y);
		return ;
	}
	x = 0;
	while (x < game->render.width)
	{
		color = fog_apply(sample_floor_tex(tex, f->grid), fog);
		render_pixel(game->render.frame, x, y, color);
		f->grid = vec2_add(f->grid, f->step);
		x++;
	}
}

/*
** Calculates world-space step and starting position for floor row
**
** The floor plane is at y=0 in world space. For each screen row,
** we calculate where rays from left/right screen edges intersect
** this plane, then linearly interpolate between them.
**
**       Camera (height = 0.5 units above floor)
**            \         |          /
**             \        |         /
**              \       |        /
**               \      |       /
**        left    \     |      /    right
**        ray      \    |     /     ray
**                  \   |    /
**                   \  |   /
**        Floor ------\-+-/------- (y = 0)
**                     \|/
**                  intersection
**
** Distance formula: dist = camera_height / row_offset
** where row_offset = abs(screen_y - horizon)
*/

static void	calc_floor_step(t_floor *f, t_game *game)
{
	t_f32	step_scale;

	step_scale = f->dist / (t_f32)game->render.width;
	f->step = vec2_mul(vec2_sub(f->right, f->left), step_scale);
	f->grid.x = game->camera.pos.x + f->left.x * f->dist;
	f->grid.y = game->camera.pos.y + f->left.y * f->dist;
}

/*
** Initializes floor rendering context for a screen row
**
** Calculates:
**   - Left/right ray directions (edges of camera frustum)
**   - Distance to floor plane at this row
**   - Horizon line position (accounting for pitch)
*/

static void	init_floor_row(t_floor *f, t_game *game, t_i32 y)
{
	t_i32		row_offset;
	t_i32		pitch;

	pitch = game->camera.pitch * game->render.height;
	f->horizon = game->render.height / 2 + pitch;
	f->left = vec2_sub(game->camera.dir, game->camera.plane);
	f->right = vec2_add(game->camera.dir, game->camera.plane);
	row_offset = absi(y - f->horizon);
	if (row_offset == 0)
		row_offset = 1;
	f->dist = (CAMERA_HEIGHT * game->render.height) / (t_f32)row_offset;
}

/*
** Renders a single horizontal row of floor or ceiling
** Multithreaded function call with height restriction
**
** Rows below horizon = floor, rows above horizon = ceiling
*/

void	render_floor_row(t_game *game, t_i32 y)
{
	t_floor	floor;
	t_tex	*tex;

	init_floor_row(&floor, game, y);
	calc_floor_step(&floor, game);
	if (y > floor.horizon)
		tex = &game->assets.textures[TEXTURE_FLOOR];
	else
		tex = &game->assets.textures[TEXTURE_CEILING];
	draw_floor_row(game, &floor, tex, y);
}
