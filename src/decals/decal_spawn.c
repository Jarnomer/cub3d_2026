/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decal_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_type	get_target_type(t_game *game, t_hit *hit)
{
	t_entity	*ent;

	if (hit->entity != INVALID_ID)
	{
		ent = darray_get(&game->entities, hit->entity);
		if (ent && ent->is_active)
			return (ent->type);
	}
	return (ENTITY_NONE);
}

static t_vec3	calc_impact_pos(t_hit *hit)
{
	t_vec3	pos;

	pos.z = hit->z_offset;
	if (hit->dir == WALL_NORTH || hit->dir == WALL_SOUTH)
		pos.x = (t_f32)hit->grid.x + hit->wall_x;
	else
		pos.y = (t_f32)hit->grid.y + hit->wall_x;
	if (hit->dir == WALL_NORTH)
		pos.y = (t_f32)hit->grid.y + 1.0f - DECAL_WALL_OFFSET;
	else if (hit->dir == WALL_SOUTH)
		pos.y = (t_f32)hit->grid.y + DECAL_WALL_OFFSET;
	else if (hit->dir == WALL_EAST)
		pos.x = (t_f32)hit->grid.x + 1.0f - DECAL_WALL_OFFSET;
	else
		pos.x = (t_f32)hit->grid.x + DECAL_WALL_OFFSET;
	return (pos);
}

static void	init_decal(t_decal *decal, t_decaldef *def, t_hit *hit)
{
	decal->pos = calc_impact_pos(hit);
	decal->dir = hit->dir;
	decal->wall_x = hit->wall_x;
	decal->dist = hit->dist;
	decal->type = def->id;
	decal->life = def->lifespan;
	decal->max_life = def->lifespan;
	decal->opacity = 1.0f;
	decal->frame = def->decal_frame;
	decal->is_active = true;
}

void	decal_spawn(t_game *game, t_hit *hit, t_ammo ammo)
{
	t_decalmgr	*mgr;
	t_decaldef	*def;
	t_decal		*decal;
	t_decal_id	type;
	t_i32		idx;

	if (!hit->hit)
		return ;
	mgr = &game->decals;
	type = decal_lookup_impact(mgr, ammo, get_target_type(game, hit));
	if (type == DECAL_NONE)
		return ;
	def = decal_get_def(mgr, type);
	if (!def)
		return ;
	idx = pool_alloc(&mgr->pool);
	if (idx < 0)
		return ;
	decal = decal_get(mgr, (t_u32)idx);
	init_decal(decal, def, hit);
	decal_start_anim(decal, def, game);
	mgr->active++;
}
