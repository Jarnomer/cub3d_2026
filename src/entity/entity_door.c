/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	door_init(t_entity *ent)
{
	ent->state = STATE_IDLE;
	ent->has_anim = true;
	ent->use_sheet = true;
	ent->sheet_id = SHEET_DOOR;
	anim_init(&ent->anim, ANIM_DOOR_IDLE);
}

bool	entity_is_door(t_entity *ent)
{
	return (ent->type == ENTITY_DOOR);
}

t_i32	door_get_frame(t_entity *ent, t_assets *assets)
{
	t_anidef	*def;

	if (!ent->has_anim)
		return (0);
	def = &assets->anidefs[ent->anim.def_id];
	return (anim_get_frame(&ent->anim, def));
}
