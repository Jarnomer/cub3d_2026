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

static void	debug_print_decals(t_decalmgr *mgr)
{
	t_decaldef	*def;
	t_i32		i;

	ft_printf("\n=== DECAL DEFINITIONS ===\n");
	i = 1;
	while (i < DECAL_COUNT)
	{
		def = &mgr->defs[i];
		ft_printf("[%d] sheet:%d anim:%d frame:%d scale:%.2f life:%.1f\n",
			i, def->sheet_id, def->anim_id, def->decal_frame,
			(double)def->scale, (double)def->lifespan);
		i++;
	}
	ft_printf("\n=== IMPACT MAPPINGS (%u) ===\n", mgr->impact_count);
	i = 0;
	while ((t_u32)i < mgr->impact_count)
	{
		ft_printf("[%d] ammo:%d target:%d -> decal:%d\n", i,
			mgr->impacts[i].ammo, mgr->impacts[i].target,
			mgr->impacts[i].decal);
		i++;
	}
	ft_printf("=== POOL: cap=%u ===\n\n", mgr->pool.capacity);
}

void	decal_init(t_decalmgr *mgr, t_u32 capacity)
{
	*mgr = (t_decalmgr){0};
	mgr->impacts = safe_calloc(capacity * sizeof(t_impactdef));
	pool_init(&mgr->pool, capacity, sizeof(t_decal));
	config_load_decals(mgr->defs);
	config_load_impacts(mgr);
	debug_print_decals(mgr);
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
