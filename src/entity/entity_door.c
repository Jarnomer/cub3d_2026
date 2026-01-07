/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
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

static void	door_start_opening(t_entity *ent)
{
	ent->state = STATE_OPENING;
	anim_play(&ent->anim, ANIM_DOOR_OPEN);
}

static void	door_start_closing(t_entity *ent)
{
	ent->state = STATE_CLOSING;
	anim_play(&ent->anim, ANIM_DOOR_CLOSE);
}

static void	door_update_open(t_entity *ent, t_f32 dt)
{
	if (!DOOR_AUTO_CLOSE)
		return ;
	ent->timer -= dt;
	if (ent->timer <= 0.0f)
		door_start_closing(ent);
}

void	door_update(t_entity *ent, t_f32 dt)
{
	if (ent->state == STATE_OPENING && ent->anim.done)
		door_set_open(ent);
	else if (ent->state == STATE_OPEN)
		door_update_open(ent, dt);
	else if (ent->state == STATE_CLOSING && ent->anim.done)
		door_set_closed(ent);
}

void	door_interact(t_entity *ent)
{
	if (ent->state == STATE_IDLE)
		door_start_opening(ent);
	else if (ent->state == STATE_OPEN)
		door_start_closing(ent);
}
