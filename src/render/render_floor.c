/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_u32	sample_floor(t_tex *tex, t_vec2 pos)
{
	t_i32	tx;
	t_i32	ty;

	tx = (t_i32)(pos.x * tex->width) % tex->width;
	ty = (t_i32)(pos.y * tex->height) % tex->height;
	if (tx < 0)
		tx += tex->width;
	if (ty < 0)
		ty += tex->height;
	return (texture_sample(tex, tx, ty));
}

static void	init_row_ctx(t_floor *f, t_game *game, t_i32 y)
{
	t_i32	p;
	t_i32	horizon;

	horizon = game->render.height / 2
		+ (t_i32)(game->camera.pitch * game->render.height);
	f->ray_left = vec2_sub(game->camera.dir, game->camera.plane);
	f->ray_right = vec2_add(game->camera.dir, game->camera.plane);
	p = absi(y - horizon);
	if (p == 0)
		p = 1;
	f->row_dist = (0.5f * game->render.height) / (t_f32)p;
	f->horizon = horizon;
}

static void	calc_floor_step(t_floor *f, t_game *game)
{
	t_f32	step_scale;

	step_scale = f->row_dist / (t_f32)game->render.width;
	f->floor_step = vec2_sub(f->ray_right, f->ray_left);
	f->floor_step = vec2_mul(f->floor_step, step_scale);
	f->floor_pos.x = game->camera.pos.x + f->ray_left.x * f->row_dist;
	f->floor_pos.y = game->camera.pos.y + f->ray_left.y * f->row_dist;
}

void	render_floor_row(t_game *game, t_i32 y)
{
	t_floor	f;
	t_i32	x;
	t_tex	*tex;
	t_u32	color;

	init_row_ctx(&f, game, y);
	calc_floor_step(&f, game);
	if (y > f.horizon)
		tex = &game->map->floor_tex;
	else if (y < f.horizon)
		tex = &game->map->ceil_tex;
	else
		return ;
	x = 0;
	while (x < game->render.width)
	{
		color = fog_blend(sample_floor(tex, f.floor_pos),
				fog_factor(f.row_dist));
		render_pixel(game->render.frame, x, y, color);
		f.floor_pos = vec2_add(f.floor_pos, f.floor_step);
		x++;
	}
}
