/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_emit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_vec3	calc_reflect_dir(t_vec2 shot_dir, t_hit *hit)
{
	t_vec3	dir;

	if (hit->axis == AXIS_X)
		dir = vec3_new(-shot_dir.x, shot_dir.y, 0.0f);
	else
		dir = vec3_new(shot_dir.x, -shot_dir.y, 0.0f);
	return (dir);
}

static t_vec3	calc_impact_pos(t_game *game, t_hit *hit)
{
	t_vec2	pos;
	t_f32	z;

	pos = vec2_mul(game->camera.dir, hit->dist - PARTICLE_WALL_OFFSET);
	pos = vec2_add(game->camera.pos, pos);
	z = game->camera.pitch * hit->dist * PARTICLE_PITCH_SCALE;
	z = clampf(z, PARTICLE_FLOOR_Z, PARTICLE_CEILING_Z);
	return (vec3_new(pos.x, pos.y, z));
}

static void	emit_particles(t_game *game, t_surfdef *def, t_hit *hit)
{
	t_vec3	pos;
	t_vec3	dir;
	t_i32	count;
	t_i32	i;

	pos = calc_impact_pos(game, hit);
	dir = calc_reflect_dir(game->camera.dir, hit);
	count = rand_rangei(def->count_min, def->count_max + 1);
	i = 0;
	while (i < count)
	{
		particle_spawn(&game->emitter, def->particle, pos, dir);
		i++;
	}
}

void	particle_emit_impact(t_game *game, t_hit *hit)
{
	t_surfdef	*def;

	if (!hit->hit)
		return ;
	def = surface_get_def(&game->emitter, hit->entity);
	if (!def || def->particle <= PARTICLE_NONE)
		return ;
	emit_particles(game, def, hit);
}
