/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	handle_floor_bounce(t_particle *particle, t_partdef *def)
{
	if (absf(particle->velocity) < PARTICLE_STOP_VEL)
	{
		particle->velocity = 0.0f;
		particle->vel = vec2_mul(particle->vel, PARTICLE_FLOOR_FRIC);
	}
	else
	{
		particle->velocity = -particle->velocity * def->bounce;
		particle->vel = vec2_mul(particle->vel, def->bounce);
	}
}

static void	update_particle(t_particle *particle, t_partdef *def, t_f32 dt)
{
	particle->velocity -= def->gravity * PARTICLE_GRAVITY * dt;
	particle->pos = vec2_add(particle->pos, vec2_mul(particle->vel, dt));
	particle->offset += particle->velocity * dt;
	if (particle->offset > PARTICLE_FLOOR_Z)
		return ;
	particle->offset = PARTICLE_FLOOR_Z;
	handle_floor_bounce(particle, def);
}

void	particle_update_all(t_emitter *emitter, t_f32 dt)
{
	t_particle	*particle;
	t_partdef	*def;
	t_u32		i;

	emitter->active_count = 0;
	i = 0;
	while (i < emitter->capacity)
	{
		particle = &emitter->particles[i];
		if (particle->is_active)
		{
			def = &emitter->partdefs[particle->type];
			particle->life -= dt;
			if (particle->life <= 0.0f)
				particle->is_active = false;
			else
				update_particle(particle, def, dt);
			if (particle->is_active)
				emitter->active_count++;
		}
		i++;
	}
}
