/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_particle_rect(t_game *game, t_rect b, t_f32 dist, t_u32 color)
{
	t_i32	x;
	t_i32	y;

	y = 0;
	while (y < b.h)
	{
		x = 0;
		while (x < b.w)
		{
			if (!zbuf_test(&game->render, b.x, dist) && color_is_opaque(color))
				render_pixel_safe(game->render.frame, b.x + x, b.y + y, color);
			x++;
		}
		y++;
	}
}

static t_u32	calc_particle_color(t_particle *particle, t_partdef *def)
{
	t_f32	factor;
	t_u32	base;
	t_u8	alpha;

	if (particle->life.max <= 0.0f)
		return (def->color.start);
	factor = clampf(1.0f - particle->life.min / particle->life.max, 0.0f, 1.0f);
	base = color_lerp(def->color.start, def->color.end,
			(t_u8)(factor * COLOR_CHANNEL_MAX));
	if (!def->is_faded)
		return (base);
	alpha = (t_u8)((1.0f - factor) * COLOR_CHANNEL_MAX);
	return (color_with_alpha(base, alpha));
}

static t_rect	calc_particle_bounds(t_game *game,
	t_particle *particle, t_partdef *def, t_vec2 trans)
{
	t_vec2i	screen;
	t_i32	size;
	t_i32	height;

	height = game->render.height;
	screen.x = (t_i32)((game->render.width / 2) * (1.0f + trans.x / trans.y));
	screen.y = height / 2 - (t_i32)(particle->pos.z * height / trans.y);
	screen.y += (t_i32)(game->camera.pitch * height);
	size = maxi(1, (t_i32)(def->size * PARTICLE_BASE_SIZE / trans.y));
	return (rect_new(screen.x - size, screen.y - size, size, size));
}

static void	draw_particle(t_game *game, t_particle *particle, t_partdef *def)
{
	t_vec2	trans;
	t_rect	bounds;
	t_u32	color;

	trans = trans_world_to_cam(&game->camera,
			vec2_new(particle->pos.x, particle->pos.y));
	if (trans_behind_camera(trans.y))
		return ;
	bounds = calc_particle_bounds(game, particle, def, trans);
	color = calc_particle_color(particle, def);
	draw_particle_rect(game, bounds, trans.y, color);
}

void	render_particles(t_game *game)
{
	t_prtclmgr	*mgr;
	t_particle	*particle;
	t_partdef	*def;
	t_u32		i;

	mgr = &game->particles;
	if (mgr->active == 0)
		return ;
	i = 0;
	while (i < mgr->capacity)
	{
		particle = &mgr->particles[i];
		if (particle->is_active)
		{
			def = &mgr->partdefs[particle->type];
			draw_particle(game, particle, def);
		}
		i++;
	}
}
