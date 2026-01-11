/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	door_start_opening(t_entity *ent)
{
	ent->state = STATE_OPENING;
	anim_play(&ent->anim, ANIM_DOOR_OPEN);
}

void	door_start_closing(t_entity *ent)
{
	ent->state = STATE_CLOSING;
	anim_play(&ent->anim, ANIM_DOOR_CLOSE);
}

void	door_update_open(t_entity *ent, t_f32 dt)
{
	if (!DOOR_AUTO_CLOSE)
		return ;
	ent->cooldown -= dt;
	if (ent->cooldown <= 0.0f)
		door_start_closing(ent);
}

void	door_set_open(t_entity *ent)
{
	ent->state = STATE_OPEN;
	ent->is_solid = false;
	ent->cooldown = DOOR_TIMER;
}

void	door_set_closed(t_entity *ent)
{
	ent->state = STATE_IDLE;
	ent->is_solid = true;
	anim_init(&ent->anim, ANIM_DOOR_IDLE);
}
