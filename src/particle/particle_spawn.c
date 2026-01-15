/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_spawn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_vec2	apply_spread(t_vec2 dir, t_f32 spread)
{
	t_f32	angle;
	t_f32	offset;

	if (spread <= 0.0f)
		return (dir);
	angle = atan2f(dir.y, dir.x);
	offset = rand_range(-spread, spread);
	return (vec2_from_angle(angle + offset));
}

static void	init_particle(t_particle *particle,
	t_partdef *def, t_vec2 pos, t_vec2 dir)
{
	t_f32	speed;

	speed = rand_range(def->speed_min, def->speed_max);
	*particle = (t_particle){.pos = pos, .offset = PARTICLE_SPAWN_Z};
	particle->type = def->id;
	particle->vel = vec2_mul(apply_spread(dir, def->spread), speed);
	particle->velocity = rand_range(0.0f, def->speed_max) * PARTICLE_Z_MULT;
	particle->life = rand_range(def->life_min, def->life_max);
	particle->lifespan = particle->life;
	particle->is_active = true;
}

void	particle_spawn_dir(t_emitter *emitter,
	t_part_id type, t_vec2 pos, t_vec2 dir)
{
	t_particle	*particle;
	t_partdef	*def;

	if (type <= PARTICLE_NONE || type >= PARTICLE_COUNT)
		return ;
	particle = particle_get_inactive(emitter);
	if (!particle)
		return ;
	def = &emitter->partdefs[type];
	init_particle(particle, def, pos, dir);
	emitter->active_count++;
}

static void	particle_spawn(t_emitter *emitter,
	t_part_id type, t_vec2 pos, t_f32 z)
{
	t_particle	*particle;
	t_partdef	*def;
	t_f32		angle;
	t_f32		speed;

	if (type <= PARTICLE_NONE || type >= PARTICLE_COUNT)
		return ;
	particle = particle_get_inactive(emitter);
	if (!particle)
		return ;
	def = &emitter->partdefs[type];
	angle = rand_range(0.0f, TAU);
	speed = rand_range(def->speed_min, def->speed_max);
	*particle = (t_particle){.pos = pos, .offset = z, .type = type};
	particle->vel = vec2_mul(vec2_from_angle(angle), speed);
	particle->life = rand_range(def->life_min, def->life_max);
	particle->velocity = rand_range(def->speed_min, def->speed_max);
	particle->velocity *= PARTICLE_Z_MULT;
	particle->lifespan = particle->life;
	particle->is_active = true;
	emitter->active_count++;
}

void	particle_spawn_all(t_emitter *emitter,
	t_part_id type, t_vec2 pos, t_i32 amount)
{
	t_i32	i;

	i = 0;
	while (i < amount)
	{
		particle_spawn(emitter, type, pos, PARTICLE_SPAWN_Z);
		i++;
	}
}
