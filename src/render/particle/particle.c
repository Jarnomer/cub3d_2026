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

void	particle_init(t_prtclmgr *mgr, size_t capacity)
{
	*mgr = (t_prtclmgr){.capacity = capacity};
	mgr->particles = safe_calloc(sizeof(t_particle) * capacity);
	config_load_particles(mgr->prtcldefs);
	config_load_surfaces(mgr->surfdefs);
}

void	particle_destroy(t_prtclmgr *mgr)
{
	if (!mgr)
		return ;
	free(mgr->particles);
	*mgr = (t_prtclmgr){0};
}

void	particle_clear(t_prtclmgr *mgr)
{
	t_u32	i;

	i = 0;
	while (i < mgr->capacity)
	{
		mgr->particles[i].is_active = false;
		i++;
	}
	mgr->active = 0;
}
