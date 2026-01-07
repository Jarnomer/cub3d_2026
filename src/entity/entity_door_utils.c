/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	door_can_interact(t_entity *ent)
{
	if (ent->state == STATE_OPENING || ent->state == STATE_CLOSING)
		return (false);
	return (true);
}

void	door_set_open(t_entity *ent)
{
	ent->state = STATE_OPEN;
	ent->solid = false;
	ent->timer = DOOR_TIMER;
}

void	door_set_closed(t_entity *ent)
{
	ent->state = STATE_IDLE;
	ent->solid = true;
	anim_init(&ent->anim, ANIM_DOOR_IDLE);
}

t_i32	door_get_frame(t_entity *ent, t_assets *assets)
{
	t_anidef	*def;

	if (!ent->has_anim)
		return (0);
	def = &assets->anidefs[ent->anim.def_id];
	return (anim_get_frame(&ent->anim, def));
}
