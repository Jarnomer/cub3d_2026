/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_barrel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	barrel_init(t_entity *ent)
{
	ent->state = STATE_IDLE;
	ent->has_anim = true;
	ent->use_sheet = true;
	ent->sheet_id = SHEET_BARREL;
	anim_init(&ent->anim, ANIM_BARREL_IDLE);
	anim_play(&ent->anim, ANIM_BARREL_IDLE);
}

void	barrel_explode(t_entity *ent)
{
	ent->state = STATE_DYING;
	ent->solid = false;
	anim_play(&ent->anim, ANIM_BARREL_EXPLODE);
}

void	barrel_death(t_entity *ent)
{
	ent->state = STATE_DEAD;
	ent->solid = false;
}
