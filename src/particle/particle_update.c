/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	handle_bounce(t_particle *particle, t_partdef *def)
{
	if (absf(particle->vel.z) < PARTICLE_STOP_VEL)
	{
		particle->vel.z = 0.0f;
		particle->vel.x *= PARTICLE_FLOOR_FRIC;
		particle->vel.y *= PARTICLE_FLOOR_FRIC;
	}
	else
	{
		particle->vel.z = -particle->vel.z * def->bounce;
		particle->vel.x *= def->bounce;
		particle->vel.y *= def->bounce;
	}
}

static void	handle_floor_collision(t_particle *particle, t_partdef *def)
{
	if (particle->pos.z > PARTICLE_FLOOR_Z)
		return ;
	particle->pos.z = PARTICLE_FLOOR_Z;
	handle_bounce(particle, def);
}

static void	handle_ceiling_collision(t_particle *particle, t_partdef *def)
{
	if (particle->pos.z < PARTICLE_CEILING_Z)
		return ;
	particle->pos.z = PARTICLE_CEILING_Z;
	particle->vel.z = -particle->vel.z * def->bounce;
}

static void	update_particle(t_particle *particle, t_partdef *def, t_f32 dt)
{
	particle->vel.z -= def->gravity * PARTICLE_GRAVITY * dt;
	particle->pos.x += particle->vel.x * dt;
	particle->pos.y += particle->vel.y * dt;
	particle->pos.z += particle->vel.z * dt;
	handle_floor_collision(particle, def);
	handle_ceiling_collision(particle, def);
}

void	particle_update_all(t_emitter *emitter, t_f32 dt)
{
	t_particle	*particle;
	t_partdef	*def;
	t_u32		i;

	emitter->active = 0;
	i = 0;
	while (i < emitter->capacity)
	{
		particle = &emitter->particles[i];
		if (particle->is_active)
		{
			def = &emitter->partdefs[particle->type];
			particle->life.min -= dt;
			if (particle->life.min <= 0.0f)
				particle->is_active = false;
			else
				update_particle(particle, def, dt);
			if (particle->is_active)
				emitter->active++;
		}
		i++;
	}
}
