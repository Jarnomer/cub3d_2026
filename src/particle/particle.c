/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	particle_init(t_emitter *emitter, size_t capacity)
{
	*emitter = (t_emitter){.capacity = capacity};
	emitter->particles = safe_calloc(sizeof(t_particle) * capacity);
	config_load_particles(emitter->partdefs);
	config_load_surfaces(emitter->surfdefs);
}

void	particle_destroy(t_emitter *emitter)
{
	if (!emitter)
		return ;
	free(emitter->particles);
	*emitter = (t_emitter){0};
}

void	particle_clear(t_emitter *emitter)
{
	t_u32	i;

	i = 0;
	while (i < emitter->capacity)
	{
		emitter->particles[i].is_active = false;
		i++;
	}
	emitter->active = 0;
}
