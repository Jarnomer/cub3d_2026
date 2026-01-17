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
	offset = rand_range(-PI / 2, PI / 2);
	dir.x = cosf(angle + offset);
	dir.y = sinf(angle + offset);
	dir.z = rand_range(-spread, spread);
	return (dir);
}

static void	init_particle(t_particle *particle,
			t_partdef *def, t_vec3 pos, t_vec3 dir)
{
	t_f32	speed;

	speed = range_random(def->speed);
	*particle = (t_particle){.pos = pos, .type = def->id};
	particle->vel = vec3_mul(apply_spread(dir, def->spread), speed);
	particle->life.min = range_random(def->life);
	particle->life.max = particle->life.min;
	particle->is_active = true;
}

void	particle_spawn(t_prtclmgr *mgr,
			t_part_id type, t_vec3 pos, t_vec3 dir)
{
	t_particle	*particle;
	t_partdef	*def;

	if (type <= PARTICLE_NONE || type >= PARTICLE_COUNT)
		return ;
	particle = particle_get_inactive(mgr);
	if (!particle)
		return ;
	def = &mgr->partdefs[type];
	if (!def)
		return ;
	init_particle(particle, def, pos, dir);
	mgr->active++;
}
