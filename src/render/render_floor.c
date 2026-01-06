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
	f->left = vec2_sub(game->camera.dir, game->camera.plane);
	f->right = vec2_add(game->camera.dir, game->camera.plane);
	p = absi(y - horizon);
	if (p == 0)
		p = 1;
	f->dist = (0.5f * game->render.height) / (t_f32)p;
	f->horizon = horizon;
}

static void	calc_floor_step(t_floor *f, t_game *game)
{
	t_f32	step_scale;

	step_scale = f->dist / (t_f32)game->render.width;
	f->step = vec2_sub(f->right, f->left);
	f->step = vec2_mul(f->step, step_scale);
	f->grid.x = game->camera.pos.x + f->left.x * f->dist;
	f->grid.y = game->camera.pos.y + f->left.y * f->dist;
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
		tex = &game->assets.textures[TEXTURE_FLOOR];
	else if (y < f.horizon)
		tex = &game->assets.textures[TEXTURE_CEILING];
	else
		return ;
	x = 0;
	while (x < game->render.width)
	{
		color = fog_blend(sample_floor(tex, f.grid),
				fog_factor(f.dist));
		render_pixel(game->render.frame, x, y, color);
		f.grid = vec2_add(f.grid, f.step);
		x++;
	}
}
