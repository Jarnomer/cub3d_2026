/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	door_can_interact(t_entity *ent)
{
	return (!door_is_animating(ent));
}

bool	door_is_animating(t_entity *ent)
{
	return (ent->state == STATE_OPENING || ent->state == STATE_CLOSING);
}

bool	door_is_blocking(t_entity *ent)
{
	return (ent->state == STATE_IDLE || ent->state == STATE_CLOSING);
}

t_i32	door_get_frame(t_entity *ent, t_assets *assets)
{
	t_anidef	*def;

	if (!ent->has_anim)
		return (0);
	def = &assets->anidefs[ent->anim.def_id];
	return (anim_get_frame(&ent->anim, def));
}
