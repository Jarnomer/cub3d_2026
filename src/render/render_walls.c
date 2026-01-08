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
	t_i32	y;
	t_i32	tex_y;
	t_u32	color;
	t_u8	fog;

	fog = lookup_fog(&game->lookup, s->dist);
	if (fog == FOG_FULL)
	{
		fog_fill_column(game, x, s->start, s->end);
		return ;
	}
	slice_calc_tex_step(s, tex->height);
	y = s->start;
	while (y <= s->end)
	{
		tex_y = clampi((t_i32)s->tex_pos, 0, tex->height - 1);
		color = texture_sample(tex, s->tex_x, tex_y);
		render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		s->tex_pos += s->tex_step;
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
	if (!ent || !ent->active)
		return ;
	if (door_is_animating(ent))
		occlude_store_door(game, hit, x);
	if (door_is_blocking(ent))
		zbuf_write(&game->render, x, hit->dist);
	render_door_column(game, hit, x);
}

void	render_wall_column(t_game *game, t_i32 x)
{
	t_ray	ray;
	t_vec2	dir;
	t_hit	wall_hit;
	t_hit	door_hit;

	occlude_clear_column(game, x);
	dir = trans_ray_dir(&game->camera, x, game->render.width);
	ray_init(&ray, game->camera.pos, dir);
	wall_hit = passthr_dda(&ray, game, RAY_MAX_DIST, &door_hit);
	if (!wall_hit.hit && door_hit.entity == ENTITY_VOID)
		return ;
	if (wall_hit.hit && wall_hit.cell != CELL_DOOR)
		render_wall(game, &wall_hit, x);
	if (door_hit.entity != ENTITY_VOID)
		handle_door(game, &door_hit, x);
	else if (wall_hit.hit && wall_hit.cell == CELL_DOOR)
		handle_door(game, &wall_hit, x);
}
