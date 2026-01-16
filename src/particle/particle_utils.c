/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_particle	*particle_get_inactive(t_emitter *emitter)
{
	t_u32	i;

	i = 0;
	while (i < emitter->capacity)
	{
		if (!emitter->particles[i].is_active)
			return (&emitter->particles[i]);
		i++;
	}
	return (NULL);
}

static t_surface	surface_from_entity(t_type entity_type)
{
	if (entity_type == ENTITY_DOOR)
		return (SURFACE_METAL);
	if (entity_type == ENTITY_BARREL)
		return (SURFACE_METAL);
	if (entity_type == ENTITY_ENEMY)
		return (SURFACE_FLESH);
	return (SURFACE_STONE);
}

t_surfdef	*surface_get_def(t_emitter *emitter, t_type type)
{
	if (type < 0 || type >= ENTITY_NONE)
		return (&emitter->surfdefs[SURFACE_STONE]);
	return (&emitter->surfdefs[surface_from_entity(type)]);
}
