/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	decal_init(t_decalmgr *mgr, t_u32 capacity)
{
	*mgr = (t_decalmgr){0};
	mgr->impacts = safe_calloc(capacity * sizeof(t_impactdef));
	pool_init(&mgr->pool, capacity, sizeof(t_decal));
	config_load_decals(mgr->defs);
	config_load_impacts(mgr);
}

void	decal_destroy(t_decalmgr *mgr)
{
	pool_destroy(&mgr->pool);
	free(mgr->impacts);
	*mgr = (t_decalmgr){0};
}

void	decal_clear(t_decalmgr *mgr)
{
	pool_reset(&mgr->pool);
	mgr->active = 0;
}
