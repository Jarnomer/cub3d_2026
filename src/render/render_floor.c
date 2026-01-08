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
		color = sample_texture_wrap(tex, f->grid.x, f->grid.y);
		render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		f->grid = vec2_add(f->grid, f->step);
		x++;
	}
}

static void	calc_floor_step(t_floor *f, t_game *game)
{
	t_f32	step_scale;

	step_scale = f->dist / (t_f32)game->render.width;
	f->step = vec2_mul(vec2_sub(f->right, f->left), step_scale);
	f->grid.x = game->camera.pos.x + f->left.x * f->dist;
	f->grid.y = game->camera.pos.y + f->left.y * f->dist;
}

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
