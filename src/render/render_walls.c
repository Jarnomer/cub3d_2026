/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_wall_column(t_game *game, t_i32 x, t_slice *s, t_tex *tex)
{
	t_u32	color;
	t_u32	fog;
	t_i32	tex_y;
	t_i32	y;

	fog = lookup_fog(&game->lookup, s->dist);
	if (color_is_solid(fog))
	{
		fog_fill_column(game, x, s->start, s->end);
		return ;
	}
	slice_calc_tex_step(s, tex->height);
	y = s->start;
	while (y <= s->end)
	{
		tex_y = clampi((t_i32)s->tex_y, 0, tex->height - 1);
		color = texture_sample(tex, s->tex_x, tex_y);
		render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		s->tex_y += s->step;
		y++;
	}
}

static void	render_wall(t_game *game, t_hit *hit, t_i32 x)
{
	t_slice	slice;
	t_tex	*tex;

	tex = &game->assets.textures[hit->dir];
	slice = slice_from_hit(hit, game->render.height, tex->width);
	slice_apply_pitch(&slice, &game->camera, game->render.height);
	zbuf_write(&game->render, x, hit->dist);
	draw_wall_column(game, x, &slice, tex);
}

static void	handle_door(t_game *game, t_hit *hit, t_i32 x)
{
	t_entity	*ent;

	if (hit->entity < 0)
		return ;
	ent = darray_get(&game->entities, hit->entity);
	if (!ent || !ent->is_active)
		return ;
	if (door_is_animating(ent) || ent->state == STATE_OPEN)
		occlude_store(game, hit, x);
	else if (door_is_blocking(ent))
		zbuf_write(&game->render, x, hit->dist);
	render_door_column(game, hit, x);
}

void	render_wall_column(t_game *game, t_i32 x)
{
	t_ray	ray;
	t_vec2	dir;
	t_hit	wall;
	t_hit	door;

	occlude_clear(game, x);
	dir = trans_ray_dir(&game->camera, x, game->render.width);
	ray_init(&ray, game->camera.pos, dir);
	wall = passthr_dda(&ray, game, RAY_MAX_DIST, &door);
	if (wall.hit && wall.cell != CELL_DOOR)
		render_wall(game, &wall, x);
	if (door.entity != INVALID_ID)
		handle_door(game, &door, x);
	else if (wall.cell == CELL_DOOR)
		handle_door(game, &wall, x);
}
