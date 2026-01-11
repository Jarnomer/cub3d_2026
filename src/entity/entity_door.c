/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
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

void	door_update(t_entity *ent, t_f32 dt)
{
	if (ent->state == STATE_OPENING && ent->anim.is_finished)
		door_set_open(ent);
	else if (ent->state == STATE_OPEN)
		door_update_open(ent, dt);
	else if (ent->state == STATE_CLOSING && ent->anim.is_finished)
		door_set_closed(ent);
}

void	door_interact(t_entity *ent)
{
	if (ent->state == STATE_IDLE)
		door_start_opening(ent);
	else if (ent->state == STATE_OPEN)
		door_start_closing(ent);
}
