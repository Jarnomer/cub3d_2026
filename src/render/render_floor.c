/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_floor_row(t_game *game, t_floor *floor, t_tex *tex, t_i32 y)
{
	t_u32	color;
	t_u32	fog;
	t_i32	x;

	fog = lookup_fog(&game->lookup, floor->dist);
	if (color_is_solid(fog))
	{
		fog_fill_row(game, y);
		return ;
	}
	x = 0;
	while (x < game->render.width)
	{
		color = texture_sample_wrap(tex, floor->grid.x, floor->grid.y);
		render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		floor->grid = vec2_add(floor->grid, floor->step);
		x++;
	}
}

static void	calc_floor_step(t_floor *floor, t_game *game)
{
	t_f32	step;

	step = floor->dist / (t_f32)game->render.width;
	floor->step = vec2_sub(floor->right, floor->left);
	floor->step = vec2_mul(floor->step, step);
	floor->grid.x = game->camera.pos.x + floor->left.x * floor->dist;
	floor->grid.y = game->camera.pos.y + floor->left.y * floor->dist;
}

static void	init_row_ctx(t_floor *floor, t_game *game, t_i32 y)
{
	t_i32	offset;

	offset = (t_i32)(game->camera.pitch * game->render.height);
	floor->horizon = game->render.height / 2 + offset;
	floor->left = vec2_sub(game->camera.dir, game->camera.plane);
	floor->right = vec2_add(game->camera.dir, game->camera.plane);
	floor->dist = camera_floor_offset(game, y);
}

void	render_floor_row(t_game *game, t_i32 y)
{
	t_floor	floor;
	t_tex	*tex;

	init_row_ctx(&floor, game, y);
	calc_floor_step(&floor, game);
	if (y > floor.horizon)
		tex = &game->assets.textures[TEXTURE_FLOOR];
	else
		tex = &game->assets.textures[TEXTURE_CEILING];
	draw_floor_row(game, &floor, tex, y);
}
