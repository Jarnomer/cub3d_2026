/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_particle_rect(t_game *game,
	t_vec2i screen, t_i32 size, t_f32 dist, t_u32 color)
{
	t_i32	x;
	t_i32	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (!zbuf_test(&game->render, screen.x, dist)
				&& color_is_opaque(color))
				render_pixel_safe(game->render.frame,
					screen.x + x, screen.y + y, color);
			x++;
		}
		y++;
	}
}

static t_u32	calc_particle_color(t_particle *particle, t_partdef *def)
{
	t_f32	blend;
	t_u32	base;
	t_u8	alpha;

	if (particle->lifespan <= 0.0f)
		return (def->color_start);
	blend = clampf(1.0f - (particle->life / particle->lifespan), 0.0f, 1.0f);
	base = color_lerp(def->color_start, def->color_end,
			(t_u8)(blend * COLOR_CHANNEL_MAX));
	if (!def->is_faded)
		return (base);
	alpha = (t_u8)((1.0f - blend) * COLOR_CHANNEL_MAX);
	return (color_with_alpha(base, alpha));
}

static void	draw_particle(t_game *game, t_particle *particle, t_partdef *def)
{
	t_vec2i	screen;
	t_vec2	trans;
	t_i32	size;
	t_i32	height;
	t_u32	color;

	trans = trans_world_to_cam(&game->camera, particle->pos);
	if (trans_behind_camera(trans.y))
		return ;
	height = game->render.height;
	screen.x = (t_i32)((game->render.width / 2) * (1.0f + trans.x / trans.y));
	screen.y = height / 2 - (t_i32)(particle->offset * height / trans.y);
	screen.y += (t_i32)(game->camera.pitch * height);
	size = maxi(1, (t_i32)(def->size * PARTICLE_BASE_SIZE / trans.y));
	screen.x -= size;
	screen.y -= size;
	color = calc_particle_color(particle, def);
	draw_particle_rect(game, screen, size, trans.y, color);
}

void	render_particles(t_game *game)
{
	t_emitter	*emitter;
	t_particle	*particle;
	t_partdef	*def;
	t_u32		i;

	emitter = &game->emitter;
	if (emitter->active_count == 0)
		return ;
	i = 0;
	while (i < emitter->capacity)
	{
		particle = &emitter->particles[i];
		if (particle->is_active)
		{
			def = &emitter->partdefs[particle->type];
			draw_particle(game, particle, def);
		}
		i++;
	}
}
