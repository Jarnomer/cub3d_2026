/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decal_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_decal_id	decal_lookup_impact(t_decalmgr *mgr, t_ammo ammo, t_type target)
{
	t_impactdef	*imp;
	t_u32		i;

	i = 0;
	while (i < mgr->impact_count)
	{
		imp = &mgr->impacts[i];
		if (imp->ammo == ammo && imp->target == target)
			return (imp->decal);
		i++;
	}
	i = 0;
	while (i < mgr->impact_count)
	{
		imp = &mgr->impacts[i];
		if (imp->ammo == ammo && imp->target == ENTITY_NONE)
			return (imp->decal);
		i++;
	}
	return (DECAL_NONE);
}

t_decal	*decal_get(t_decalmgr *mgr, t_u32 index)
{
	return ((t_decal *)pool_get(&mgr->pool, index));
}

t_decaldef	*decal_get_def(t_decalmgr *mgr, t_decal_id id)
{
	if (id <= DECAL_NONE || id >= DECAL_COUNT)
		return (NULL);
	return (&mgr->defs[id]);
}
