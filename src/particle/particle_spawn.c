/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_spawn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_vec3	apply_spread(t_vec3 dir, t_f32 spread)
{
	t_f32	angle;
	t_f32	offset;

	if (spread <= 0.0f)
		return (dir);
	angle = atan2f(dir.y, dir.x);
	offset = rand_range(-spread, spread);
	dir.x = cosf(angle + offset);
	dir.y = sinf(angle + offset);
	dir.z += rand_range(-spread, spread);
	return (dir);
}

static void	init_particle(t_particle *particle,
			t_partdef *def, t_vec3 pos, t_vec3 dir)
{
	t_f32	speed;

	speed = rand_range(def->speed_min, def->speed_max);
	*particle = (t_particle){.pos = pos};
	particle->type = def->id;
	particle->vel = vec3_mul(apply_spread(dir, def->spread), speed);
	particle->life = rand_range(def->life_min, def->life_max);
	particle->lifespan = particle->life;
	particle->is_active = true;
}

void	particle_spawn(t_emitter *emitter,
			t_part_id type, t_vec3 pos, t_vec3 dir)
{
	t_particle	*particle;
	t_partdef	*def;

	if (type <= PARTICLE_NONE || type >= PARTICLE_COUNT)
		return ;
	particle = particle_get_inactive(emitter);
	if (!particle)
		return ;
	def = &emitter->partdefs[type];
	if (!def)
		return ;
	init_particle(particle, def, pos, dir);
	emitter->active_count++;
}
