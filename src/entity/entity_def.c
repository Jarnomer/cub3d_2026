/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_def.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

/*
** Static entity definitions table
** Format: {type, sprite_id, scale, health, solid}
*/

static const t_entdef	g_entity_defs[ENTITY_COUNT] = {
	[ENTITY_NONE] = {ENTITY_NONE, 0, 1.0f, 0, false},
	[ENTITY_BARREL] = {ENTITY_BARREL, SPRITE_BARREL, 0.7f, 20, true},
	[ENTITY_DOOR] = {ENTITY_DOOR, SPRITE_DOOR_CLOSED, 1.0f, 0, true},
	[ENTITY_PICKUP_HP] = {ENTITY_PICKUP_HP, SPRITE_PICKUP_HP, 0.5f, 0, false},
	[ENTITY_PICKUP_AMMO] = {ENTITY_PICKUP_AMMO, SPRITE_PICKUP_AMMO, 0.5f, 0, false},
	[ENTITY_ENEMY] = {ENTITY_ENEMY, 0, 1.0f, 100, true},
	[ENTITY_PLAYER] = {ENTITY_PLAYER, 0, 1.0f, 100, true},
};

const t_entdef	*entity_get_def(t_type type)
{
	if (type >= ENTITY_COUNT)
		return (&g_entity_defs[ENTITY_NONE]);
	return (&g_entity_defs[type]);
}

void	entity_apply_def(t_entity *ent, const t_entdef *def)
{
	ent->tex_id = def->sprite_id;
	ent->scale = def->scale;
	ent->health = def->health;
	ent->solid = def->solid;
}
